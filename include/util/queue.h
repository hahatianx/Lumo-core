#pragma once

#include "util/link_list.h"

typedef struct queue {
    list_t link;
    int size;
    void* obj;
} queue_t;

void queue_init(queue_t *que);
int queue_empty(queue_t *que);
void queue_push(queue_t *que, void* obj);
void queue_pop(queue_t *que);
queue_t* queue_head(queue_t *que);
int queue_size(queue_t *que);

#define queue_get_obj(que, type) ((type*)(queue_head(que)->obj))
