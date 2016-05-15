#include <pthread.h>

#include "server_thread.h"

void Thread::start() {
    pthread_create(&thread, NULL, Thread::runner, this);
}

void Thread::join() {
    pthread_join(thread, NULL);
}

void* Thread::runner(void* data) {
        Thread* self = (Thread*)data;
        self->run();
        return self;
}

Thread::~Thread() {}
