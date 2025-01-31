/**
 *
 * FEC header definition.
 *
 */
#ifndef FEC_DEFS_H_
#define FEC_DEFS_H_

#define FRAME_SIZE_TYPE uint16_t

struct fec_header {
    // NOTE: The order of block and class_id are switched from the definition in P4!
	uint8_t block_id : 5; // The block ID of the FEC
	uint8_t class_id : 3; // The class of the packet
	uint8_t index; // The index or pkt ID of withing the block.
    uint16_t orig_ethertype;
    uint16_t packet_len;
};

#define WHARF_ETHERTYPE 0x081C
#define MAX_BLOCK 6
#define FRAME_SIZE_CUTOFF 1498

#endif
