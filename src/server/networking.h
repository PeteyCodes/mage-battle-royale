#ifndef NETWORKING_H
#define NETWORKING_H

#include "network_packet.h"

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>


struct network_client_t {
    struct addrinfo *addr;
    struct network_client_t *next;
};

struct network_context_t {
    int listen_socketfd;
};

struct network_context_t * net_initialize();
int net_listen(struct network_context_t *ctx);
struct network_client_t *net_add_client(struct addrinfo *addr);
network_packet_t *net_read_packet(struct network_context_t *ctx);
int net_shutdown(struct network_context_t *ctx);

void *get_in_addr(struct sockaddr *sa);

#endif
