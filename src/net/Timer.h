#ifndef __TIMER_H__
#define __TIMER_H__

#include <net/NonCopyable.h>

#include <base/Types.h>
#include <base/Timestamp.h>

#include <functional>

namespace cppevt
{

class Timer : private NonCopyable
{
public:
    typedef std::function<void()> TimerCallback;

    explicit Timer();
    ~Timer() = default;

    int create();
    int setExpiration(const Timestamp& expiration);

    int fd() { return fd_; }
    void callback();
    void setCallback(const TimerCallback& cb) { cb_ = cb; }

private:
    TimerCallback cb_;
    bool isRepeat_;
    double interval_;
    Timestamp expiration_;
    int fd_;
};

} // namespace cppevt

#endif