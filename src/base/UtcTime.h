#ifndef __UTC_TIME_H__
#define __UTC_TIME_H__

#include <base/Types.h>

#include <string>

namespace cppevt
{

class UtcTime
{
public:
    UtcTime();
    ~UtcTime() = default;
    explicit UtcTime(uint64_t microSeconds);

    void now();
    std::string toString() const;
    uint64_t get() const { return microSecondsSinceEpoch_; }
    bool isValid() { return (microSecondsSinceEpoch_ > 0); }

    bool operator==(const UtcTime& utc) 
    { return (microSecondsSinceEpoch_ == utc.get()); }
    bool operator<(const UtcTime& utc)
    { return (microSecondsSinceEpoch_ < utc.get()); }
    bool operator>(const UtcTime& utc)
    { return (microSecondsSinceEpoch_ > utc.get()); }
    UtcTime& operator=(const UtcTime& utc)
    {
        microSecondsSinceEpoch_ = utc.get();
        return *this;
    }
    UtcTime& operator=(uint64_t microSeconds)
    {
        microSecondsSinceEpoch_ = microSeconds;
        return *this;
    }

    static const int kMicroSecondsPerSecond = 1000 * 1000;

private:
    std::string formatTimeStamp(uint64_t seconds, uint64_t microSeconds) const;

    uint64_t microSecondsSinceEpoch_;
};

}

#endif