#ifndef NETWORK_PACKET_H
#define NETWORK_PACKET_H

#include <stdlib.h>

typedef enum  {
    PKT_TEST = 0,
    PKT_TYPE_COUNT
} network_packet_type_e;

typedef struct {
    network_packet_type_e packet_type;
    size_t payload_size;
    void *payload;
} network_packet_t;


#endif
