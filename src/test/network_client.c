#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Usage: network_client hostname\n");
        exit(-1);
    }

    struct addrinfo hints, *serv_info;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int rv;
    if ((rv = getaddrinfo(argv[1], "1313", &hints, &serv_info)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return -1;
    }

    int sockfd;
    struct addrinfo *p;
    for (p = serv_info; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("socket: client");
            return -1; 
        }

        printf("Trying to connect...\n");
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("connect: client");
            continue;
        }

        break;
    }

    if (p == NULL) {
        printf("Failed to connect to server\n");
        exit(-1);
    }

    char buffer[100];
    buffer[99] = '\0';
    int bytecount = recv(sockfd, &buffer, 99, 0);
    if (bytecount == -1) {
        perror("recv");
        exit(-1);
    }

    printf("Client received: %s\n", buffer);

    close(sockfd);

    return 0;
}

