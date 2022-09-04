#pragma once

typedef void* (*threadstarter_t)(void*);

typedef struct g_thread {
    // thread input struct
    threadstarter_t main;
    void* args;

    void* sys_thread;
} thread_meta_t;

int thread_start(thread_meta_t*);
int thread_terminate(thread_meta_t*);

#define thread_cancelpoint() pthread_testcancel()