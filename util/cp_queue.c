#include "util/cp_queue.h"

void cp_queue_init(cp_queue_t *que) {
    queue_init(&que->que);
    mutex_init(&que->m);
    mutex_cond_init(&que->cv);
}

void produce_obj(cp_queue_t *que, void* obj) {
    mutex_lock(&que->m);
    queue_push(&que->que, obj);
    mutex_cond_signal(&que->cv);
    mutex_unlock(&que->m);
}

void* cp_queue_obj(cp_queue_t *que) {
    void *obj;
    mutex_cond_lock(&que->m, &que->cv, !queue_empty(&que->que)) {
        obj = queue_get_obj(&que->que, void);
        queue_pop(&que->que);
    } mutex_cond_unlock(&que->m);
    return obj;
}