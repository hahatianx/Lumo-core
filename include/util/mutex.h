#pragma once

#if defined(__unix__) || defined(__APPLE__)

#include <pthread.h>

typedef pthread_mutex_t mutex_t;
typedef pthread_cond_t cond_t;

#define mutex_init(m) pthread_mutex_init(m, NULL)
#define mutex_lock(m) pthread_mutex_lock(m)
#define mutex_unlock(m) pthread_mutex_unlock(m)

#define mutex_cond_init(cv) pthread_cond_init(cv, NULL)
#define mutex_cond_signal(cv) pthread_cond_signal(cv)
#define mutex_cond_broadcast(cv) pthread_cond_broadcast(cv)

#define mutex_cond_lock(m, cv, exp_until)                          \
    do {                                                           \
        pthread_mutex_lock(m);                                     \
        while(!(exp_until))                                        \
            pthread_cond_wait((cv), (m));                          \
        do                                                        

#define mutex_cond_unlock(m)                                       \
        while(0);                                                  \
        pthread_mutex_unlock(m);                                   \
    } while(0);                                                    

#elif defined(_WIN32) || defined(__WIN32)
#endif