#ifndef _THREAD_H
#define _THREAD_H

#include <pthread.h>

class Thread {
    private:
        pthread_t thread;

        static void* runner(void* data) {
            Thread* self = (Thread*) data;
            self->run();
            return self;
        }

        Thread(const Thread&);
        Thread& operator=(const Thread&);

    public:
        Thread() {}
        
        void start() {
            pthread_create(&thread, NULL, Thread::runner, this);
        }

        void join() {
            pthread_join(thread, NULL);
        }

        virtual void run() = 0;
        virtual ~Thread() {}
};

#endif
