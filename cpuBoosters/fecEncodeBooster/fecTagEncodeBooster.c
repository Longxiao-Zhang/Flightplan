#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fecBooster.h"

int lastBlockId = 0;
/**
 * @brief      packet handler function for pcap
 *
 * @param      args    The arguments
 * @param[in]  header  The header
 * @param[in]  packet  The packet
 */
void my_packet_handler(
    u_char *args,
    const struct pcap_pkthdr *header,
    const u_char *packet
) {
	if (workerCt > 1){
		fprintf(stderr, "This booster doesn't work across workers at present\n");
		exit(1);
	}

	u_char *new_packet = NULL;
	int tagged_size = wharf_tag_frame(packet, header->len, &new_packet);

	const struct fec_header *fecHeader = (struct fec_header *) (new_packet + SIZE_ETHERNET);

	if (fecHeader->block_id != lastBlockId){
		lastBlockId = fecHeader->block_id;
		zeroout_block_in_pkt_buffer(lastBlockId);
	}

	if (fecHeader->index < NUM_DATA_PACKETS){
		forward_frame(new_packet, tagged_size);
	}

	/*Update the received pkt in the pkt buffer.*/
	if (pkt_buffer_filled[fecHeader->block_id][fecHeader->index] == PACKET_ABSENT) {
		FRAME_SIZE_TYPE *original_frame_size = (FRAME_SIZE_TYPE *)(pkt_buffer[fecHeader->block_id][fecHeader->index]);
		*original_frame_size = fecHeader->size;
		memcpy(pkt_buffer[fecHeader->block_id][fecHeader->index] + sizeof(FRAME_SIZE_TYPE), packet, header->len);
		pkt_buffer_filled[fecHeader->block_id][fecHeader->index] = PACKET_PRESENT;
	} 
	else {
		fprintf(stderr, "Tagging produced a duplicate index\n");
		exit(1);
	}

	/*check if the block is ready for processing*/
	if (is_all_data_pkts_recieved_for_block(fecHeader->block_id)) {
		/*populate the global fec structure for rse encoder and call the encode.*/
		call_fec_blk_get(fecHeader->block_id);

		/* Encoder */
		encode_block();

		copy_parity_packets_to_pkt_buffer_DEPRECATED(fecHeader->block_id);
// FIXME tag the parity packets

		/*Inject all packets in the block back to the network*/
		for (int i = NUM_DATA_PACKETS; i < NUM_DATA_PACKETS+NUM_PARITY_PACKETS; i++) {
			char* packetToInject = pkt_buffer[fecHeader->block_id][i];
			size_t outPktLen = get_total_packet_size(packetToInject);
			forward_frame(packetToInject, outPktLen);

// FIXME how to get size of parity pakcets

// but don't encapsulate ethernet header
tagged_size = wharf_tag_frame(packet, header->len, &new_packet);

		}
	}
	return;
}
