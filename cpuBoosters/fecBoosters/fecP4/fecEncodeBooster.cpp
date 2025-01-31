#include "fecBooster.h"
#include "fecEncodeBooster.hpp"
#include <chrono>
#include <mutex>

static void encode_and_forward(tclass_type tclass, int egress_port, encode_forward_fn forward,
                               int block_id, int k, int h) {
    FRAME_SIZE_TYPE hdr_size = sizeof(struct ether_header);
    u_char hdr_packet[hdr_size];
    struct ether_header *hdr_ether = (struct ether_header *)hdr_packet;
    hdr_ether->ether_type = 0;

    size_t empty_size = WHARF_TAG_SIZE;
    u_char empty_packet[empty_size];
    for (int i=0; i < k; i++) {
        if (!pkt_already_inserted(tclass, egress_port, block_id, i)) {
            wharf_tag_data(tclass, block_id, i,
                           hdr_packet, hdr_size, empty_packet, &empty_size);
            LOG_INFO("Forwarding empty packet size %zu", empty_size);
            forward(empty_packet, empty_size, egress_port);
            insert_into_pkt_buffer(tclass, egress_port, block_id, i,
                                   hdr_size, hdr_packet);
        }
    }

    FRAME_SIZE_TYPE template_size;
    u_char *template_packet = retrieve_from_pkt_buffer(tclass, egress_port, block_id,
                                                       0, &template_size);
    struct ether_header *template_header = (struct ether_header *)template_packet;

    populate_fec_blk_data(tclass, egress_port, block_id);
    encode_block();

    size_t parity_size;
    for (int i = k; i < (k + h); i++) {
        u_char *parity_pkt = retrieve_encoded_packet(tclass, i, &parity_size);
        size_t tagged_size = parity_size + WHARF_TAG_SIZE;
        u_char tagged_pkt[tagged_size];

        wharf_tag_parity(tclass, block_id, i,
                         parity_pkt, parity_size,
                         tagged_pkt, &tagged_size);

        LOG_INFO("Forwarding parity packet with size %zd", tagged_size);
        struct ether_header *parity_hdr = (struct ether_header*)tagged_pkt;
        memcpy(parity_hdr->ether_dhost, template_header->ether_dhost, ETH_ALEN);
        memcpy(parity_hdr->ether_shost, template_header->ether_shost, ETH_ALEN);
        forward(tagged_pkt, tagged_size, egress_port);
    }
}

using std::chrono::steady_clock;

static steady_clock::time_point timeouts[TCLASS_MAX + 1][MAX_PORT + 1];

static steady_clock::time_point zero_time = timeouts[0][0];

static std::mutex encoder_mutex;

void fec_encode_timeout_handler(encode_forward_fn forward) {
    // Lock encoding while checking timeouts
    std::lock_guard<std::mutex> lock(encoder_mutex);

    for (int egress_port = 0; egress_port <= MAX_PORT; egress_port++) {
        for (int tclass = 0; tclass <= TCLASS_MAX; tclass++) {
            if (timeouts[tclass][egress_port] != zero_time &&
                    timeouts[tclass][egress_port] < steady_clock::now()) {
                timeouts[tclass][egress_port] = zero_time;
                int block_id = get_fec_block_id(tclass, egress_port);
                LOG_INFO("Timeout reached for class %d port %d block %d",
                         tclass, egress_port, block_id);
                fec_sym k, h;
                get_fec_params(tclass, &k, &h);
                encode_and_forward(tclass, egress_port, forward, block_id, k, h);
                mark_pkts_absent(tclass, egress_port, block_id);
                advance_block_id(tclass, egress_port);
            }
        }
    }
}

void fec_encode_p4_packet(const u_char *pkt, size_t pkt_size,
                          const struct fec_header *fec, int egress_port,
                          int k, int h, int t,
                          encode_forward_fn forward) {
    // Must put egress on odd numbers to not overlap with ingress
    egress_port = egress_port * 2 + 1;

    LOG_INFO("Hitting lock guard");
    // Lock while encoding in progress
    std::lock_guard<std::mutex> lock(encoder_mutex);

    LOG_INFO("Fec_encode called for packet %d: %d.%d",
             (int)fec->class_id, (int)fec->block_id, (int)fec->index);

    tclass_type tclass = fec->class_id;

    // TODO: This shouldn't have to be done every time this is called
    set_fec_params(tclass, k, h);

    LOG_INFO("Inserting pkt of tclass %d size %zu into buffer (block %d)",
            (int)tclass, pkt_size, (int)fec->block_id);
    int rtn = insert_into_pkt_buffer(tclass, egress_port, fec->block_id, fec->index, pkt_size, pkt);
    if (rtn != 0) {
        LOG_ERR("Error inserting into pkt buffer");
        return;
    }

    // If advancing the packet index would start a new block
    if (fec->index == (k - 1)) {
        LOG_INFO("Encoding and forwarding block");
        encode_and_forward(tclass, egress_port, forward, fec->block_id, k, h);
        timeouts[tclass][egress_port] = zero_time;
        mark_pkts_absent(tclass, egress_port, fec->block_id);
    } else if (fec->index == 0) {
        LOG_INFO("Resetting tclass %d timer", tclass);
        timeouts[tclass][egress_port] = steady_clock::now() + std::chrono::milliseconds(t);
    }
}
