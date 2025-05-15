#include <base/UtcTime.h>

#include <sys/time.h>

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace cppevt;

UtcTime::UtcTime()
    : microSecondsSinceEpoch_(0)
{
}

UtcTime::UtcTime(uint64_t microSeconds)
    : microSecondsSinceEpoch_(microSeconds)
{
}

void UtcTime::now()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    microSecondsSinceEpoch_ = tv.tv_sec * kMicroSecondsPerSecond + tv.tv_usec;
}

std::string UtcTime::toString() const
{
    uint64_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
    uint64_t microSeconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;

    return formatTimeStamp(seconds, microSeconds);
}

std::string UtcTime::formatTimeStamp(uint64_t seconds, uint64_t microSeconds) const
{
    std::ostringstream oss;
    oss << seconds << "." << std::setw(6) << std::setfill('0') << microSeconds;
    return oss.str();
}
