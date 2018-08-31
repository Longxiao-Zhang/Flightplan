#ifndef MEMCACHED_H_
#define MEMCACHED_H_


using mcd_forward_fn = std::function<void(char *payload, size_t)>;

bool call_memcached(char *packet, size_t packet_size, mcd_forward_fn forward);


#endif
