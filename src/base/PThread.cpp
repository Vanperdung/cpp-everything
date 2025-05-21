#include <base/PThread.h>

#include <stdexcept>
#include <iostream>
using namespace cppevt;

PThread::PThread(ThreadFunc func = nullptr, void* arg = nullptr)
    : func_(func), 
    arg_(arg), 
    joined_(false),
    detached_(false),
    stack_size_(0),
    priority_(0),
    policy_(0)
{
    pthread_attr_init(&attr_);
}

PThread::~PThread()
{
    pthread_attr_destroy(&attr_);
    if (!joined_ && !detached_)
        join();
}

status_t PThread::create()
{
    if (func_ == nullptr)
    {
        std::cout << "Thread function is not set" << std::endl;
        return CPPEVT_ERROR;    
    }

    if (tid_ != 0)
    {
        std::cout << "Thread already created" << std::endl;
        return CPPEVT_ERROR;
    }

    int ret = pthread_create(&tid_, &attr_, func_, arg_);
    if (ret != 0)
    {
        std::cout << "Failed to create thread" << std::endl;
        return CPPEVT_ERROR;
    }

    return CPPEVT_OK;
}

status_t PThread::join()
{
    if (joined_)
    {
        std::cout << "Thread already joined" << std::endl;
        return CPPEVT_ERROR;
    }

    if (detached_)
    {
        std::cout << "Thread already detached" << std::endl;
        return CPPEVT_ERROR;
    }

    joined_ = true;
    pthread_join(tid_, nullptr);
}

status_t PThread::detach()
{
    if (joined_)
    {
        std::cout << "Thread already joined" << std::endl;
        return CPPEVT_ERROR;
    }

    if (detached_)
    {
        std::cout << "Thread already detached" << std::endl;
        return CPPEVT_ERROR;
    }

    pthread_detach(tid_);
    detached_ = true;
}

bool PThread::joinable() const
{
    return !joined_ && !detached_;
}

bool PThread::detached() const
{
    return detached_;
}

void PThread::setStackSize(size_t size)
{
    pthread_attr_setstacksize(&attr_, size);
    stack_size_ = size;
}

size_t PThread::getStackSize() const
{
    return stack_size_;
}

void PThread::setPriority(int priority)
{
    struct sched_param param;

    param.sched_priority = priority;
    pthread_attr_setschedparam(&attr_, &param);
    priority_ = priority;
}

int PThread::getPriority() const
{
    return priority_;
}

void PThread::setName(const std::string& name)
{
    name_ = name;
    if (tid_ != 0)
        pthread_setname_np(tid_, name_.c_str());
}

std::string PThread::getName() const
{
    return name_;
}

void PThread::setSchedPolicy(int policy)
{
    pthread_attr_setschedpolicy(&attr_, policy);
    policy_ = policy;
}

int PThread::getSchedPolicy() const
{
    return policy_;
}

