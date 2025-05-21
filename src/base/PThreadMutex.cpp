#include <base/PThreadMutex.h>

using namespace cppevt;

PThreadMutex::PThreadMutex()
{
    pthread_mutex_init(&mutex_, NULL);
}

PThreadMutex::~PThreadMutex()
{
    pthread_mutex_destroy(&mutex_);
}

void PThreadMutex::lock()
{
    pthread_mutex_lock(&mutex_);
}

void PThreadMutex::unlock()
{
    pthread_mutex_unlock(&mutex_);
}

// Try to lock the mutex, return true if success, false if failed
[[nodiscard]] bool PThreadMutex::tryLock()
{
    return pthread_mutex_trylock(&mutex_) == 0;
}