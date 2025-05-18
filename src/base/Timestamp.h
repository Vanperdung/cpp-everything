#ifndef __TIMESTAMP_H__
#define __TIMESTAMP_H__

#include <base/Types.h>

#include <string>

namespace cppevt
{

class Timestamp
{
public:
    Timestamp();
    Timestamp(uint64_t microSeconds);
    ~Timestamp() = default;

    void now();
    std::string toString() const;
    uint64_t get() const { return microSecondsSinceEpoch_; }
    bool isValid() { return (microSecondsSinceEpoch_ > 0); }

    bool operator==(const Timestamp& ts) 
    { return (microSecondsSinceEpoch_ == ts.get()); }
    bool operator<(const Timestamp& ts)
    { return (microSecondsSinceEpoch_ < ts.get()); }
    bool operator>(const Timestamp& ts)
    { return (microSecondsSinceEpoch_ > ts.get()); }
    Timestamp& operator=(const Timestamp& ts)
    {
        microSecondsSinceEpoch_ = ts.get();
        return *this;
    }
    Timestamp& operator=(uint64_t microSeconds)
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