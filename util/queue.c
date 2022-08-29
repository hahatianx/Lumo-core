#include <stdlib.h>

#include "util/queue.h"
#include "core.h"


void queue_init(queue_t *que) {
    list_init(&que->link);
    que->size = 0;
}

int queue_empty(queue_t *que) {
    return !que->size;
}

void queue_push(queue_t *que, void* obj) {
    queue_t *new_node = new(queue_t);
    new_node->obj = obj;
    ++ que->size;
    list_insert_tail(&que->link, &new_node->link);
}

void queue_pop(queue_t *que) {
    queue_t *top = list_head_item(&que->link, queue_t, link);
    list_remove_head(&que->link);
    -- que->size;
    free(top);
}

queue_t* queue_head(queue_t *que) {
    return list_head_item(&que->link, queue_t, link);
}

int queue_size(queue_t *que) {
    return que->size;
}
