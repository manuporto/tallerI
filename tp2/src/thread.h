/*
 * ============================================================================
 *
 *       Filename:  thread.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/04/16 13:58:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * ============================================================================
 */

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
