#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "network/message.h"
#include "format.h"

inline
int message_to_block(message_t *msg, char *buffer, uint32_t size) {
    memset(buffer, 0, size);
    uint32_t m_size = msg->size;
    uint32_serialize_to_network(&m_size);
    memcpy(buffer, &m_size, 4);
    memcpy(buffer + 4, &msg->msg, msg->size);
    return 0;
}

inline
int block_to_message(char *buffer, message_t *msg, uint32_t size) {
    memset(msg, 0, size);
    uint32_t m_size;
    memcpy(&m_size, buffer, 4);
    network_serialize_to_uint32(&m_size);
    msg->size = m_size;
    memcpy(&msg->msg, buffer + 4, size - 4);
    return 0;
}