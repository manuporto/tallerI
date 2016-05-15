#ifndef _MUTEX_H
#define _MUTEX_H

#include <pthread.h>

class Mutex {
   public:
    Mutex();
    void lock();
    void unlock();
    ~Mutex();
    Mutex(const Mutex&);
    Mutex& operator=(const Mutex&);

   private:
    pthread_mutex_t mutex;
};

class Lock {
   public:
    explicit Lock(Mutex& m);
    ~Lock();
    Lock(const Lock&);
    Lock& operator=(const Lock&);

   private:
    Mutex& m;
};

#endif
