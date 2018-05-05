
#include <stdio.h>
#include "networking.h"


int main()
{

    struct network_context_t *ctx = net_initialize();
    if (ctx == NULL) {
          fprintf(stderr, "Failed to initialize networking.\n");
          return -1;
    }

    // TODO - Listen for client connections

    // TODO - Server loop

    return 0;
}

