#include <stdio.h>
#include <assert.h>

#include "util/cp_queue.h"
#include "util/queue.h"
#include "thread/thread.h"
#include "test.h"

cp_queue_t que;
thread_meta_t thrd;
int value[] = {0, 1, 2, 3, 4};

void* consumer_handler(void* args) {
    cp_queue_t *que = (cp_queue_t*)args;
    while (1) {
        int *value = consume_obj(que, int);
        printf("received value %d\n", *value);
    }
    return NULL;
}

void test_cp_queue_signals() {
    cp_queue_init(&que);
    thrd.args = (void*)(&que);
    thrd.main = (threadstarter_t)consumer_handler;
    thread_start(&thrd);
    for (int i = 0; i < 5; i ++) {
        produce_obj(&que, (void*)(&value[i]));
    }
}

int main() {
    RUN_TEST(test_cp_queue_signals(), "produce 4 and consumer should receive 4");
    return 0;
}