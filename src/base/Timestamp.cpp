#include <base/Timestamp.h>

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <string.h>

#include <sys/time.h>

using namespace cppevt;

Timestamp::Timestamp()
{
    memset(&timestamp_, 0, sizeof(struct timespec));
}

Timestamp::Timestamp(struct timespec timestamp)
{
    timestamp_.tv_sec = timestamp.tv_sec;
    timestamp_.tv_nsec = timestamp.tv_nsec;
}

Timestamp::Timestamp(uint64_t sec, uint64_t nsec)
{
    timestamp_.tv_sec = sec;
    timestamp_.tv_nsec = nsec;
}

void Timestamp::now()
{
    ::clock_gettime(CLOCK_MONOTONIC, &timestamp_);
}

std::string Timestamp::toString() const
{
    std::ostringstream oss;
    oss << timestamp_.tv_sec << "." << std::setw(9) << \
        std::setfill('0') << timestamp_.tv_nsec;
    return oss.str();
}
