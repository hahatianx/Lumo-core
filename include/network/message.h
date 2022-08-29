#pragma once

#include <stdlib.h>

#include "core.h"
#include "format.h"

/**
 * @brief 
 * the message structure
 * The maximum overall size of a message is 1MB
 *         the size here should be <= 2^20 - 4
 */
typedef struct message {
    // the message size except the header (-4 byes)
    // maximum: 2^20 - 4
    uint32_t size;
    char *msg;
} message_t;

/**
 * @brief 
 * the task structure
 * All messages sent to and from should be in this format
 *   They should be one a queue
 */
typedef struct message_task {
    uint32_t dst_addr;
    uint32_t size;
    message_t *msg;
} message_task_t;

int message_to_block(message_t*, char*, uint32_t);
int block_to_message(char*, message_t*, uint32_t);
