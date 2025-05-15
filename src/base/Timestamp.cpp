#include <base/Timestamp.h>

#include <sys/time.h>

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace cppevt;

Timestamp::Timestamp()
    : microSecondsSinceEpoch_(0)
{
}

Timestamp::Timestamp(uint64_t microSeconds)
    : microSecondsSinceEpoch_(microSeconds)
{
}

void Timestamp::now()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    microSecondsSinceEpoch_ = tv.tv_sec * kMicroSecondsPerSecond + tv.tv_usec;
}

std::string Timestamp::toString() const
{
    uint64_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
    uint64_t microSeconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;

    return formatTimeStamp(seconds, microSeconds);
}

std::string Timestamp::formatTimeStamp(uint64_t seconds, uint64_t microSeconds) const
{
    std::ostringstream oss;
    oss << seconds << "." << std::setw(6) << std::setfill('0') << microSeconds;
    return oss.str();
}
