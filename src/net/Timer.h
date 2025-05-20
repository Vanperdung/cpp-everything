#ifndef __TIMER_H__
#define __TIMER_H__

#include <net/NonCopyable.h>
#include <net/Channel.h>

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
    ~Timer();

    status_t create();
    status_t set(const Timestamp& expiration,
                    const Timestamp& interval);
    status_t get(Timestamp& expiration, Timestamp& interval);

    void callTimerCallback();
    void setCallback(const TimerCallback& cb) { cb_ = cb; }

    Channel* channel() { return &channel_; }
    int fd() { return fd_; }

private:
    void expiredEventHandler(uint32_t revents, void *data);

    bool repeat_;
    TimerCallback cb_;
    Timestamp interval_;
    Timestamp expiration_;
    Channel channel_;
    int fd_;
};

} // namespace cppevt

#endif