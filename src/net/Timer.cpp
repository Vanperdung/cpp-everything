#include <net/Timer.h>

#include <cstring>
#include <cerrno>
#include <iostream>

#include <sys/timerfd.h>
#include <unistd.h>

using namespace cppevt;

Timer::Timer()
    : repeat_(false),
    fd_(-1),
    channel_(fd_)
{
}

Timer::~Timer()
{
    // FIXME: Is it necessary to stop timer before closing?
    if (fd_ >= 0)
        ::close(fd_);
}

status_t Timer::create()
{
    int fd = ::timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC);
    if (fd < 0)
    {
        std::cerr << "Cannot create timerfd: " << \
                    std::strerror(errno) << \
                    std::endl;
        return CPPEVT_ERROR;
    }

    fd_ = fd;
    channel_.set_fd(fd);

    return CPPEVT_OK;
}

status_t Timer::set(const Timestamp& expiration,
                        const Timestamp& interval)
{
    struct itimerspec it;
    memset(&it, 0, sizeof(struct itimerspec));

    // Timer expiration
    it.it_value = expiration.get();
    
    // Timer repeatation interval
    it.it_interval = interval.get();

    int ret = ::timerfd_settime(fd_, TFD_TIMER_ABSTIME, &it, NULL);
    if (ret < 0)
    {
        std::cerr << "Cannot set timerfd: " << \
                    std::strerror(errno) << \
                    std::endl;
        return CPPEVT_ERROR;
    }

    expiration_ = expiration;
    interval_ = interval;

    repeat_ = (interval_.get().tv_sec || interval_.get().tv_nsec);

    return CPPEVT_OK;
}

status_t Timer::get(Timestamp& expiration, Timestamp& interval)
{
    struct itimerspec it;
    memset(&it, 0, sizeof(struct itimerspec));

    int ret = ::timerfd_gettime(fd_, &it);
    if (ret < 0)
    {
        std::cerr << "Cannot set timerfd: " << \
                    std::strerror(errno) << \
                    std::endl;
        return CPPEVT_ERROR;
    }

    expiration = it.it_value;
    interval = it.it_interval;

    return CPPEVT_OK;
}

void Timer::callTimerCallback()
{
    if (cb_)
        cb_();
}