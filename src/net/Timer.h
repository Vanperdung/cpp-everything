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

    Timer(const TimerCallback& cb, Timestamp& expiration, const double interval);
    ~Timer() = default;

    void run();
    void setCallback(const TimerCallback& cb) { cb_ = cb; }
    void repeat();
    void clear();

private:
    TimerCallback cb_;
    bool isRepeat_;
    double interval_;
    Timestamp expiration_;
};

} // namespace cppevt

#endif