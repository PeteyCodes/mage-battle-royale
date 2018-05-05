#ifndef NETWORKING_H
#define NETWORKING_H

#include "network_packet.h"

struct network_client_t {
    struct addrinfo *addr;
    struct network_client_t *next;
};

struct network_context_t {
    int read_socketfd;
    int write_socketfd;
};

struct network_context_t * net_initialize();
int net_listen(struct network_context_t *ctx);
struct network_client_t *net_add_client(struct addrinfo *addr);
network_packet_t *net_read_packet(struct network_context_t *ctx);
int net_shutdown(struct network_context_t *ctx);

#endif
