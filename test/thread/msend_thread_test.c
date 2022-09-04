#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "core.h"
#include "util/queue.h"
#include "util/cp_queue.h"
#include "network/message.h"
#include "thread/thread.h"
#include "thread/msend_thread.h"

cp_queue_t sender_queue;
queue_t msg_que;

char mm[10];

int main() {
    thread_meta_t thrd;
    thrd.main = (threadstarter_t)sys_main;
    thrd.args = NULL;
    thread_start(&thrd);
    queue_init(&msg_que);
    sleep(5);
    for (int i = 0; i < 10; i ++) {
        message_task_t *task = new(message_task_t);
        message_t *msg = (message_t*)malloc(5); 
        task->dst_addr = 0x7F000001;
        msg->size = 1;
        mm[i] = 'a' + i;
        memcpy(&msg->msg, &mm[i], 1);
        task->size = 5;
        task->msg = msg;
        queue_push(&msg_que, (void*)task);
        put_message_into_sender_que(task);
    }
    put_message_into_sender_que(NULL);
    thread_terminate(&thrd);
    while (!queue_empty(&msg_que)) {
        message_task_t *front = queue_get_obj(&msg_que, message_task_t);
        queue_pop(&msg_que);
        free(front->msg);
        free(front);
    }
}