#include "thread/mrecv_thread.h"
#include "network/message.h"
#include "network/message_recv.h"

static size_t MAX_BUFFER_SIZE = 1024 * 1024;

void* sys_main(void* args) {
    message_task_t task;
    recv_message(&task, MAX_BUFFER_SIZE);
}