#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <base/NonCopyable.h>

#include <pthread.h>

namespace cppevt
{

class PThreadMutex : private NonCopyable
{
public:
    explicit PThreadMutex();
    ~PThreadMutex();

    void lock();
    void unlock();
    bool tryLock();

private:
    pthread_mutex_t mutex_;
};

} // namespace cppevt

#endif