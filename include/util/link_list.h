#pragma once

#include "core.h"

typedef struct link {
    struct link *l_prev;
    struct link *l_next;
} list_t, list_link_t;

#define list_link_init(link)                                                            \
    do {                                                                                \
        (link)->l_next = (link)->l_prev = NULL;                                         \
    } while(0);                                                                       

#define list_init(list)                                                                 \
    do {                                                                                \
        (list)->l_next = (list)->l_prev = (list);                                       \
    } while(0);                                                                       

#define list_insert_after(a, b)                                                         \
    do {                                                                                \
        list_link_t *prev = (a);                                                        \
        list_link_t *next = (b);                                                        \
        next->l_prev = prev;                                                            \
        next->l_next = prev->l_next;                                                    \
        prev->l_next->l_prev = next;                                                    \
        prev->l_next = next;                                                            \
    } while(0);                                                                       

#define list_insert_head(head, link)                                                    \
    list_insert_after(head, link)                                                      

#define list_insert_tail(head, link)                                                    \
    list_insert_after((head)->l_prev, link)                                            

#define list_remove(link)                                                               \
    do {                                                                                \
        list_link_t *cur = (link);                                                      \
        list_link_t *prev = cur->l_prev;                                                \
        list_link_t *next = cur->l_next;                                                \
        next->l_prev = prev;                                                            \
        prev->l_next = next;                                                            \
        cur->l_prev = cur->l_next = NULL;                                               \
    } while(0);                                                                       

#define list_remove_head(head)                                                          \
    list_remove((head)->l_next)                                                        

#define list_remove_tail(head)                                                          \
    list_remove((head)->l_prev)                                                        

#define list_item(link, type, member)                                                   \
    (type*)((char*)(link) - offset(type, member))                                      

#define list_head_item(head, type, member)                                              \
    list_item((head)->l_next, type, member)                                             

#define list_iterate_begin(head, var, type, member)                                     \
    do {                                                                                \
        list_link_t *_link;                                                             \
        list_link_t *_next;                                                             \
        for (_link = (head)->l_next;                                                    \
             _link != (head);                                                           \
             _link = _next) {                                                           \
                var = list_item(_link, type, member);                                   \
                _next = _link->l_next;                                                  \
                do                                                                     

#define list_iterate_reverse(head, var, type, member)                                   \
    do {                                                                                \
        list_link_t *_link;                                                             \
        list_link_t *_next;                                                             \
        for (_link = (head)->l_prev;                                                    \
             _link != (head);                                                           \
             _link = _link->l_prev) {                                                   \
                var = list_item(_link, type, member);                                   \
                do      

#define list_iterate_end()                                                              \
                while (0);                                                              \
        }                                                                               \
    } while(0);                                                                        

#define list_empty(head)                                                                \
    ((head)->l_prev == (head))                               