#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include "core.h"
#include "thread/thread.h"


int thread_start(thread_meta_t *thread_meta) {
    pthread_t *thrd = new(pthread_t);
    int result_code = pthread_create(thrd, NULL, thread_meta->main, thread_meta->args);
    if (result_code) {
        perror("pthread_create() failed.");
        exit(-1);
    }
    thread_meta->sys_thread = (void*)thrd;
    return 0;
}

void thread_terminate(thread_meta_t *thread_meta) {
    pthread_join(thread_meta->sys_thread, NULL);
    free(thread_meta->sys_thread);
}
