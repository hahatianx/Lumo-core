#include "util/cp_queue.h"
#include "thread/thread.h"
#include "thread/msend_thread.h"
#include "network/message_send.h"

extern cp_queue_t sender_queue;

void init() {
    cp_queue_init(&sender_queue);
}

void run_sender() {
    while (1) {
        message_task_t *task = consume_obj(&sender_queue, message_task_t);
        if (task == NULL) break;
        send_message(task);
    }
}

void put_message_into_sender_que(message_task_t *task) {
    produce_obj(&sender_queue, (void*)task);
}

void* sys_main(void* args) {
    init();
    run_sender();
    return NULL;
}