#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "util/queue.h"
#include "test.h"

typedef struct obj {
    int val;
} obj_t;

queue_t *que;

void init_queue() {
    que = new(queue_t);
    queue_init(que);
}

void clean_up_queue() {
    while (!queue_empty(que)) {
        queue_pop(que);
    }
}

void obj_push_test() {
    init_queue();
    obj_t *obj_1 = new(obj_t); obj_1->val = 1;
    obj_t *obj_2 = new(obj_t); obj_2->val = 2;
    obj_t *obj_3 = new(obj_t); obj_3->val = 3;
    queue_push(que, (void*)obj_1);
    queue_push(que, (void*)obj_2);
    ASSERT_TEST(!queue_empty(que), "check queue not empty");
    ASSERT_TEST(2 == queue_size(que), "check queue size = 2");
    obj_t *front;
    front = queue_get_obj(que, obj_t);
    ASSERT_TEST(front->val == obj_1->val, "check the first value = 1");
    queue_pop(que);
    front = queue_get_obj(que, obj_t);
    ASSERT_TEST(front->val == obj_2->val, "check the first value = 2");
    queue_pop(que);
    ASSERT_TEST(queue_empty(que), "check que empty");
    queue_push(que, (void*)obj_3);
    front = queue_get_obj(que, obj_t);
    ASSERT_TEST(front->val == obj_3->val, "check the first value = 3");
    clean_up_queue();
    free(obj_1);
    free(obj_2);
    free(obj_3);
}

int main() {
    RUN_TEST(obj_push_test(), "object push func test");
}