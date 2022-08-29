#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "util/link_list.h"
#include "test.h"


typedef struct node {
    int val;
    list_link_t link;
} node_t;
node_t *head;

void init_list() {
    head = new(node_t);
    list_init(&head->link);
    for (int i = 0; i < 10; i ++) {
        node_t *x = new(node_t);
        list_link_init(&x->link)
        x->val = i;
        list_insert_tail(&head->link, &x->link);
    }
}

void clean_up_list() {
    while (!list_empty(&head->link)) {
        node_t *cur = list_head_item(&head->link, node_t, link);
        list_remove_head(&head->link);
        free(cur);
    }
    free(head);
}

void order_test() {
    init_list();
    node_t *iter;
    int it = 0;
    list_iterate_begin(&head->link, iter, node_t, link) {
        ASSERT_TEST(it++ == iter->val, "check value equals");
    } list_iterate_end();
    clean_up_list();
}

void reverse_test() {
    init_list();
    node_t *iter;
    int it = 9;
    list_iterate_reverse(&head->link, iter, node_t, link) {
        ASSERT_TEST(it-- == iter->val, "check value equals");
    } list_iterate_end();
    clean_up_list();
}

void head_test() {
    init_list();
    int it = 0;
    while (!list_empty(&head->link)) {
        node_t *cur = list_head_item(&head->link, node_t, link);
        ASSERT_TEST(it++ == cur->val, "check value equals");
        list_remove_head(&head->link);
    }
}

int main() {
    RUN_TEST(order_test(), "list ordering test");
    RUN_TEST(reverse_test(), "list reverse order test");
    RUN_TEST(head_test(), "list getting head test");
    return 0;
}