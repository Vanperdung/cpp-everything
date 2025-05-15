#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <net/NonCopyable.h>

#include <pthread.h>

namespace cppevt
{

class PThreadMutex : private NonCopyable
{
public:
    PThreadMutex();
    ~PThreadMutex();

    void lock();
    void unlock();

private:
    pthread_mutex_t mutex_;
};

} // namespace cppevt

#endif