#include <net/Timer.h>

using namespace cppevt;

Timer::Timer(const TimerCallback& cb, Timestamp& expiration, const double interval)
    : cb_(cb), expiration_(expiration), interval_(interval)
{
    isRepeat_ = (interval_ > 0);
}

void Timer::run()
{
    if (cb_)
        cb_();
}

void Timer::clear()
{
    isRepeat_ = false;
    interval_ = 0;
    expiration_ = 0;
}

void Timer::repeat()
{
    if (isRepeat_)
        expiration_ = Timestamp(interval_ * 1000000 + expiration_.get());
    else
        clear();
}



