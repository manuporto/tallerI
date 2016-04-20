#ifndef _MUTEX_H
#define _MUTEX_H

#include <pthread.h>

class Mutex {
   public:
    Mutex();
    void lock();
    void unlock();
    ~Mutex();

   private:
    Mutex(const Mutex&);
    Mutex& operator=(const Mutex&);
    pthread_mutex_t mutex;
};

class Lock {
   public:
    explicit Lock(Mutex& m);
    ~Lock();

   private:
    Lock(const Lock&);
    Lock& operator=(const Lock&);
    Mutex& m;
};

#endif
