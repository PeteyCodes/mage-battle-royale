#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "networking.h"

#define SERVER_PORT         "1313"
#define MAX_BUFFER_SIZE     1024
#define BACKLOG             10



// -- Public Interface Methods --

struct network_context_t * net_initialize()
{
    // Allocate our context
    struct network_context_t *ctx = calloc(1, sizeof(struct network_context_t));

    // Get our IP and setup our networking environment
    struct addrinfo hints = {.ai_family = AF_UNSPEC, .ai_socktype = SOCK_STREAM, .ai_flags = AI_PASSIVE};

    struct addrinfo *serv_info = NULL;
    struct addrinfo *p = NULL;
    int rv; 
    if ((rv = getaddrinfo(NULL, SERVER_PORT, &hints, &serv_info)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return NULL;
    }

    // Loop through the results and bind to the first one we can
    for (p = serv_info; p != NULL; p = p->ai_next) {
        int sockfd = 0;
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            // Failed with this attempt - try the next
            continue;
        }        

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            // Failed with this attempt - try the next
            close(sockfd);
            continue;
        }

        // If we get here, we're bound, so we're done looking
        ctx->listen_socketfd = sockfd;
        break;
    }

    if (p == NULL) {
        fprintf(stderr, "Failed to bind socket\n");
        return NULL;
    }

    freeaddrinfo(serv_info);

    return ctx;
}

int net_listen(struct network_context_t *ctx)
{
    // Listen for connections and accept them as they come in
    if (listen(ctx->listen_socketfd, BACKLOG) == -1) {
        fprintf(stderr, "Failed to listen on socket\n");
        return -1;
    } 

    printf("Waiting for connections...\n");

    return 0;
}

network_packet_t * net_read_packet(struct network_context_t *ctx) 
{
    // TODO: Implement for realz
    return NULL;
}

int net_shutdown(struct network_context_t *ctx)
{
    // Shut down all connections
    // Clean up context
    // TODO: Implement for realz

    return 0;
}

// Get socket address, IPv4 or IPv6
void * get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}


