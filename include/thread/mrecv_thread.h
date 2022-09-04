#include "network/message.h"

typedef struct recv_thread_input {
    int sockfd;
    cp_queue_t *send_que;
} recv_thread_input_t;

void sys_main(void*);