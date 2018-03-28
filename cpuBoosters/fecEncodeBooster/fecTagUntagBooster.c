#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fecBooster.h"

void my_packet_handler(
    u_char *args,
    const struct pcap_pkthdr *header,
    const u_char *packet
) {
	u_char *new_packet = (u_char *)malloc(1500/*FIXME const*/);
	memcpy(new_packet, packet, header->len);
	int tagged_size = wharf_tag_frame(new_packet, header->len);
	int new_size = wharf_strip_frame(new_packet, tagged_size);
	if (new_size != header->len) {
		fprintf(stderr, "Frame size changed\n");
		exit(1);
	}
	for (int i = 0; i < header->len; i++) {
		if (new_packet[i] != packet[i]) {
			fprintf(stderr, "Frame changed\n");
			exit(1);
		}
	}
	pcap_inject(handle, new_packet, new_size);
	free(new_packet);
}
