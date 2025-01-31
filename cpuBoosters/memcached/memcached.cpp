#include "MemHLS.h"
#include "memcached.h"
#include <algorithm>

#define ETH_SIZE ((16 + 48 + 48)/8)
#define UDP_SIZE ((16 + 16 + 16 + 16)/8)
#define IPV4_SIZE ((32 + 32 + 16 + 8 + 8+ 13 + 3 + 16 + 16 + 8 + 4 + 4)/8)

static int in_offset;
template <int size_bits>
const char* cp_in(ap_uint<size_bits> &dst, const char *src) {
    //std::cout << "Parsing " << size_bits << " bits starting at byte " << (int)( src - src_orig) << ", Offset: " << in_offset << std::endl;
    uint64_t src_bits = *(uint64_t*)src;

    char *start = (char*)&src_bits;
    char *end = start + (size_bits + 8 - 1)/8;

    src_bits <<= in_offset;
    std::reverse(start, end);
    src_bits >>= (64 - size_bits)% 8;
    //src_bits >>= in_offset;

    dst = (ap_uint<size_bits>)(src_bits);

    const char *rtn = src + (size_bits + in_offset) / 8;
    in_offset = (size_bits + in_offset) % 8;
    //std::cout << "Finished Parsing " << size_bits << " bits starting at byte " << (int)( src - src_orig) << ", Offset now: " << in_offset << std::endl;
    return rtn;
}

static int out_offset;
template <int size_bits>
unsigned char *cp_out(ap_uint<size_bits> &src, unsigned char *dst){
    uint64_t src_bits = (uint64_t)src;
    char *start = (char*)&src_bits;
    char *end = start + (size_bits + 8 - 1) / 8;

    std::reverse(start, end);
    //src_bits >>= out_offset;
    src_bits <<= (64 - (size_bits + out_offset)) % 8;

    for (int i=0; i < (size_bits + out_offset + 7) / 8; i++) {
        dst[i] |= start[i];
    }

    dst = dst + (size_bits + out_offset) / 8;
    out_offset = (size_bits + out_offset) % 8;
    return dst;
}

void transfer_in(input_tuples &input_tuple, const char *packet) {
    const char *sv = packet;

    tuple_eth &eth = input_tuple.Hdr.Eth;
    sv = cp_in(eth.Dst, sv);
    sv = cp_in(eth.Src, sv);
    sv = cp_in(eth.Type, sv);

    tuple_ipv4 &ipv4 = input_tuple.Hdr.Ipv4;
    sv = cp_in(ipv4.version, sv);
    sv = cp_in(ipv4.ihl, sv);
    sv = cp_in(ipv4.diffserv, sv);
    sv = cp_in(ipv4.totallen, sv);
    sv = cp_in(ipv4.identification, sv);
    sv = cp_in(ipv4.flags, sv);
    sv = cp_in(ipv4.fragoffset, sv);
    sv = cp_in(ipv4.ttl, sv);
    sv = cp_in(ipv4.protocol, sv);
    sv = cp_in(ipv4.hdrchecksum, sv);
    sv = cp_in(ipv4.srcAddr, sv);
    sv = cp_in(ipv4.dstAddr, sv);

    tuple_udp &udp = input_tuple.Hdr.Udp;
    sv = cp_in(udp.sport, sv);
    sv = cp_in(udp.dport, sv);
    sv = cp_in(udp.len, sv);
    sv = cp_in(udp.chksum, sv);

    std::cout << "Parsed " << (int)(sv - (char*)packet) << " bytes" << std::endl;
}

uint16_t ccsum(void *buf, size_t buflen) {
    uint32_t r = 0;
    size_t len = buflen;

    const uint16_t* d = reinterpret_cast<const uint16_t*>(buf);

    while (len > 1)
    {
        r += *d++;
        len -= sizeof(uint16_t);
    }

    if (len)
    {
        r += *reinterpret_cast<const uint8_t*>(d);
    }

    while (r >> 16)
    {
        r = (r & 0xffff) + (r >> 16);
    }

    return static_cast<uint16_t>(~r);
}

template <typename T>
void transfer_out(T &input_tuple, char *packet) {
    unsigned char *sv = (unsigned char*)packet;

    tuple_eth &eth = input_tuple.Hdr.Eth;
    sv = cp_out(eth.Dst, sv);
    sv = cp_out(eth.Src, sv);
    sv = cp_out(eth.Type, sv);


    tuple_ipv4 &ipv4 = input_tuple.Hdr.Ipv4;
    ipv4.hdrchecksum = 0;
    unsigned char *start_sv = sv;
    sv = cp_out(ipv4.version, sv);
    sv = cp_out(ipv4.ihl, sv);
    sv = cp_out(ipv4.diffserv, sv);
    sv = cp_out(ipv4.totallen, sv);
    sv = cp_out(ipv4.identification, sv);
    sv = cp_out(ipv4.flags, sv);
    sv = cp_out(ipv4.fragoffset, sv);
    sv = cp_out(ipv4.ttl, sv);
    sv = cp_out(ipv4.protocol, sv);
    unsigned char *chk_sv = sv;
    // This really shouldn't be necessary, but it appears to not
    // copy over the hdrchecksum of 0 the second time...
    memset(sv, 0, sizeof(uint16_t));
    sv = cp_out(ipv4.hdrchecksum, sv);
    sv = cp_out(ipv4.srcAddr, sv);
    sv = cp_out(ipv4.dstAddr, sv);

    uint16_t csum = ccsum(start_sv, sv - start_sv);
    ipv4.hdrchecksum = csum;
    memcpy(chk_sv, &csum, sizeof(csum));

    tuple_udp &udp = input_tuple.Hdr.Udp;
    udp.chksum = 0;
    sv = cp_out(udp.sport, sv);
    sv = cp_out(udp.dport, sv);
    sv = cp_out(udp.len, sv);
    sv = cp_out(udp.chksum, sv);
}

#define CHECK(field) \
    if (input_tuple1.Hdr.field != input_tuple.Hdr.field) { \
        std::cout << "NO MATCH: " # field << std::endl; \
    } else { \
        std::cout << "MATCH " << std::endl; \
    }

bool call_memcached(const char *packet, size_t packet_size, mcd_forward_fn forward) {

    if (packet_size < ETH_SIZE + UDP_SIZE + IPV4_SIZE) {
        std::cout << "Packet size too small!" << std::endl;
        return false;
    }

    input_tuples input_tuple;
    transfer_in(input_tuple, packet);

    tuple_eth &eth = input_tuple.Hdr.Eth;
    /*
    std::cout << "Eth type " << eth.Type.to_string(16) << std::endl;
    std::cout << "Eth Src " << eth.Src.to_string(16) << std::endl;
    std::cout << "Eth Dst " << eth.Dst.to_string(16) << std::endl;
    */
    tuple_ipv4 &ipv4 = input_tuple.Hdr.Ipv4;
    /*
    std::cout << "IPv4 Version " << ipv4.version.to_string(16) << std::endl;
    std::cout << "IPv4 IHL " << ipv4.ihl.to_string(16) << std::endl;
    std::cout << "IPv4 ID " << ipv4.identification.to_string(16) << std::endl;
    std::cout << "IPv4 flags" << ipv4.flags.to_string(16) << std::endl;
    std::cout << "IPv4 frag" << ipv4.fragoffset.to_string(16) << std::endl;
    std::cout << "IPv4 TTL " << ipv4.ttl.to_string(16) << std::endl;
    std::cout << "IPv4 Protocol " << ipv4.protocol.to_string(16) << std::endl;
    std::cout << "IPv4 Checksum " << ipv4.hdrchecksum.to_string(16) << std::endl;
    std::cout << "IPv4 Src " << ipv4.srcAddr.to_string(16) << std::endl;
    std::cout << "IPv4 Dst " << ipv4.dstAddr.to_string(16) << std::endl;
*/
    tuple_udp &udp = input_tuple.Hdr.Udp;
    /*
    std::cout << "UDP checksum " << udp.chksum.to_string(16) << std::endl;
    std::cout << "UDP Dst " << udp.dport.to_string(16) << std::endl;
    std::cout << "UDP Src " << udp.sport.to_string(16) << std::endl;
    std::cout << "UDP Len " << udp.len.to_string(16) << std::endl;
*/
    input_tuple.Memcached_input.Stateful_valid = 1;
	input_tuple.Ioports.Egress_port = 0;
	input_tuple.Ioports.Ingress_port = 0;
	input_tuple.Local_state.Id = 0;
	input_tuple.Parser_extracts.Size = 0;
	input_tuple.Checkcache.forward = 0;

    hls::stream<input_tuples> input_tuple_stream;
    input_tuple_stream.write(input_tuple);

    hls::stream<packet_interface> packet_input_stream;
    unsigned int n_words = DIVIDE_AND_ROUNDUP(packet_size, BYTES_PER_WORD);
    for (unsigned int i = 0; i < n_words; i++) {
        ap_uint<MEM_AXI_BUS_WIDTH> word = 0;
        for (int j = 0; j < BYTES_PER_WORD; j++) {
            word <<= 8;
            unsigned offset = BYTES_PER_WORD * i + j;
            if (offset < packet_size) {
                word |= (unsigned char)packet[offset];
            }
        }
        bool at_end = i == n_words - 1;
        packet_interface input;
        input.Data = word;
        input.Start_of_frame = i == 0;
        input.End_of_frame = at_end;
        input.Count = packet_size % BYTES_PER_WORD;
        if (input.Count == 0 || !at_end)
            input.Count = 8;
        input.Error = 0;
        packet_input_stream.write(input);
    }

    hls::stream<output_tuples> output_tuple_stream;
    hls::stream<packet_interface> packet_output_stream;

    Memcore(input_tuple_stream, output_tuple_stream, packet_input_stream, packet_output_stream);

    packet_interface output;

    bool drop = true;
    int pkt_num = 0;
    while (1) {
        output_tuples output_tuple = output_tuple_stream.read();
        char output_packet[2048];
        int packet_i = 0;
        do {
            output = packet_output_stream.read();
            for (int i = 0; i < output.Count; i++)
            {
                char Byte = (output.Data >> (8 * (BYTES_PER_WORD - i -1))) & 0xFF;
                output_packet[packet_i++] = Byte;
            }
        } while (!output.End_of_frame);

        transfer_out(output_tuple, output_packet);
        pkt_num++;

        if (output_tuple.Hdr.Udp.sport == input_tuple.Hdr.Udp.dport) {
            forward(output_packet, packet_i, true);
        } else {
            //std::cout << "NOT dropping packet " << std::endl;
            drop = false;
        }

        if (output_tuple.Checkcache.forward != 1) {
            break;
        }
    }
    if (drop) {
        //std::cout << "YES dropping packet " << std::endl;
    }
    return drop;
}
