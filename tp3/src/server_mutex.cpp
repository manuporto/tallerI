#include <pthread.h>

#include "server_mutex.h"

/* MUTEX */

Mutex::Mutex() {
    pthread_mutex_init(&this->mutex, NULL);
}

void Mutex::lock() {
    pthread_mutex_lock(&this->mutex);
}

void Mutex::unlock() {
    pthread_mutex_unlock(&this->mutex);
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&this->mutex);
}

/* LOCK */

Lock::Lock(Mutex& m) : m(m) {
    m.lock();
}

Lock::~Lock() {
    m.unlock();
}