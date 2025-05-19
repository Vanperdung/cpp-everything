#ifndef __TIMESTAMP_H__
#define __TIMESTAMP_H__

#include <base/Types.h>

#include <string>

#include <time.h>

namespace cppevt
{

class Timestamp
{
public:
    Timestamp();
    Timestamp(struct timespec timestamp);
    ~Timestamp() = default;

    void now();
    std::string toString() const;
    struct timespec get() const { return timestamp_; }

    bool operator==(const Timestamp& ts) 
    {
        if (timestamp_.tv_sec == ts.get().tv_sec &&
            timestamp_.tv_nsec == ts.get().tv_nsec)
            return true;

        return false;
    }
    Timestamp& operator=(const Timestamp& ts)
    {
        timestamp_.tv_sec = ts.get().tv_sec;
        timestamp_.tv_nsec = ts.get().tv_nsec;

        return *this;
    }
    Timestamp& operator=(struct timespec timestamp)
    {
        timestamp_.tv_sec = timestamp.tv_sec;
        timestamp_.tv_nsec = timestamp.tv_nsec;

        return *this;
    }

private:
    struct timespec timestamp_; 
};

}

#endif