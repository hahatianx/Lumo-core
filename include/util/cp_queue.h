#pragma once

#include "util/mutex.h"
#include "util/queue.h"

typedef struct cp_queue {
    queue_t que;
    mutex_t m;
    cond_t cv;
} cp_queue_t;

void cp_queue_init(cp_queue_t*);
void produce_obj(cp_queue_t*, void*);
void* cp_queue_obj(cp_queue_t*);

#define consume_obj(cp_queue, type) ((type*)cp_queue_obj((cp_queue)))