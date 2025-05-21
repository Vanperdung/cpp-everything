#ifndef __PTHREAD_H__
#define __PTHREAD_H__

#include <base/NonCopyable.h>
#include <base/PThreadMutex.h>
#include <base/Types.h>

#include <functional>
#include <string>

#include <pthread.h>

namespace cppevt
{

class PThread : private NonCopyable
{
public:
    typedef void* (*ThreadFunc)(void*);

    explicit PThread(ThreadFunc func, void* arg);
    ~PThread();

    // Thread control methods
    status_t create();
    status_t join();
    status_t detach();

    bool joinable() const;
    bool detached() const;

    // Thread attributes
    void setStackSize(size_t size);
    size_t getStackSize() const;

    // Thread priority
    void setPriority(int priority);
    int getPriority() const;

    // Thread name
    void setName(const std::string& name);
    std::string getName() const;

    // Thread scheduling policy
    void setSchedPolicy(int policy);
    int getSchedPolicy() const;

private:
    pthread_t tid_;
    bool joined_;
    bool detached_;
    pthread_attr_t attr_;
    std::string name_;
    int priority_;
    size_t stack_size_;
    int policy_;
    ThreadFunc func_;
    void* arg_;
};

} // namespace cppevt

#endif