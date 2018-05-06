
#include <stdio.h>
#include <stdbool.h>
#include "networking.h"


int main()
{

    struct network_context_t *ctx = net_initialize();
    if (ctx == NULL) {
          fprintf(stderr, "Failed to initialize networking.\n");
          return -1;
    }

    // Listen for client connections
    if (net_listen(ctx) == -1) {
        fprintf(stderr, "Failed to listen on port");
        return -1;
    }

    // Server loop
    while (true) {
        struct sockaddr_storage client_addr;
        socklen_t ca_size = sizeof client_addr;
        int new_socketfd = accept(ctx->listen_socketfd, (struct sockaddr *)&client_addr, &ca_size);
        if (new_socketfd == -1) {
            perror("accept");
            continue;
        }

        char ip_string[INET6_ADDRSTRLEN];
        inet_ntop(client_addr.ss_family, get_in_addr((struct sockaddr *)&client_addr), ip_string, sizeof ip_string); 
        printf("Server accepted connection from: %s", ip_string);

        if (!fork()) {
            // This is the child process
            close(ctx->listen_socketfd);

            // TODO: Do server stuff!

            // TEST CODE BEGIN
            if (send(new_socketfd, "Hello from the server!", 23, 0) == -1) {
                perror("send");
            } 
            close(new_socketfd);
            exit(0);
            // TEST CODE END

        } else {
            // This is the parent
            close(new_socketfd);
        }

    }

    return 0;
}

