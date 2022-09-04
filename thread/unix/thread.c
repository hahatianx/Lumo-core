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

int thread_terminate(thread_meta_t *thread_meta) {
    int ret_code = pthread_join(*((pthread_t*)thread_meta->sys_thread), NULL);
    if (ret_code) {
        perror("pthread_join() failed.");
        exit(ret_code);
    }
    free(thread_meta->sys_thread);
    return 0;
}
