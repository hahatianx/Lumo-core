#pragma once

#include "core.h"

#define byte_swap(a, b)                                              \
    do {                                                             \
        char *na = (char*)(a);                                       \
        char *nb = (char*)(b);                                       \
        char tmp = *(na);                                            \
        *(na) = *(nb);                                               \
        *(nb) = tmp;                                                 \
    } while(0);                                                      

#define uint32_serialize_to_network(num_ptr)                         \
    do {                                                             \
        char *t = (char*)(num_ptr);                                  \
        if (__ENDIAN == __LITTLE_ENDIAN) {                           \
            byte_swap(t, t + 3);                                     \
            byte_swap(t + 1, t + 2);                                 \
        }                                                            \
    } while(0);                                                  

#define network_serialize_to_uint32(num_ptr)                         \
    do {                                                             \
        char *t = (char*)(num_ptr);                                  \
        if (__ENDIAN == __LITTLE_ENDIAN) {                           \
            byte_swap(t, t + 3);                                     \
            byte_swap(t + 1, t + 2);                                 \
        }                                                            \
    } while(0);
