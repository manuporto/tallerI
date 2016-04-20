#ifndef _THREAD_H
#define _THREAD_H

#include <pthread.h>

class Thread {
   public:
    void start();
    void join();
    virtual void run() = 0;
    virtual ~Thread();

   private:
    static void* runner(void* data);
    Thread(const Thread&);
    Thread& operator=(const Thread&);
    pthread_t thread;
};

#endif
