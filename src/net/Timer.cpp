#include <net/Timer.h>

#include <cstring>
#include <cerrno>

#include <sys/timerfd.h>
#include <unistd.h>

using namespace cppevt;

Timer::Timer()
    : cb_(NULL),
    interval_(-1), 
    isRepeat_(false),
    fd_(-1)
{
}

Timer::~Timer()
{
    // FIXME: Is it necessary to stop timer before closing?
    if (fd_ > 0)
        ::close(fd_);
}

int Timer::create()
{
    int ret = ::timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC);
    if (ret < 0)
        throw std::runtime_error(std::string("::timerfd_create: ") + std::strerror(errno));

    return ret;
}

int Timer::stop()
{
    struct itimerspec it;

    
}

int Timer::setExpiration(const Timestamp& expiration)
{
    struct itimerspec it;
    memset(&it, 0, sizeof(struct itimerspec));

    it.it_value.tv_sec = expiration.get() / Timestamp::kMicroSecondsPerSecond;
    it.it_value.tv_nsec = expiration.get() % Timestamp::kMicroSecondsPerSecond;
    it.it_interval.tv_sec = it.it_value.tv_sec;
    it.it_interval.tv_nsec = it.it_value.tv_nsec;

    int ret = ::timerfd_settime(fd_, TFD_TIMER_ABSTIME, &it, NULL);
    if (ret < 0)
        throw std::runtime_error(std::string("::timerfd_settime: ") + std::strerror(errno));

    expiration_ = expiration;
    isRepeat_ = true;

    return ret;
}

void Timer::callback()
{
    if (cb_)
        cb_();
}



