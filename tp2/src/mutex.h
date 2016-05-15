#ifndef _MUTEX_H
#define _MUTEX_H

#include <pthread.h>

class Mutex {
    private:
        pthread_mutex_t mutex;

        Mutex(const Mutex&);
        Mutex& operator=(const Mutex&);

    public:
        Mutex() {
            pthread_mutex_init(&this->mutex, NULL);
        }

        void lock() {
            pthread_mutex_lock(&this->mutex);
        }

        void unlock() {
            pthread_mutex_unlock(&this->mutex);
        }

        ~Mutex() {
            pthread_mutex_destroy(&this->mutex);
        }
};

class Lock {
    private:
        Mutex &m;

        Lock(const Lock&);
        Lock& operator=(const Lock&);

    public:
        explicit Lock(Mutex &m) : m(m) {
            m.lock();
        }

        ~Lock() {
            m.unlock();
        }
};

#endif
