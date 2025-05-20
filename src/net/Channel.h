#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include <net/EventLoop.h>

#include <base/NonCopyable.h>
#include <base/Types.h>

#include <functional>

#include <stdint.h>

namespace cppevt
{

class EventLoop;

class Channel : private NonCopyable
{
public:
    explicit Channel(int fd);
    ~Channel();

    typedef std::function<void(uint32_t, void*)> EventCallback;

    int fd() const { return fd_; }
    void set_fd(int fd) { fd_ = fd; }
    
    uint32_t events() const { return events_; }
    uint32_t revents() const { return revents_; }

    void set_events(uint32_t events);
    void set_revents(uint32_t revents);

    void setEventCallback(const EventCallback& cb);
    void callEventCallback();

    void setEventLoopOwner(EventLoop *owner);
    EventLoop* getEventLoopOwner();

    void onEventLoopOwnerDistroyed();

    void setEventData(void *data);

private:
    int fd_;
    uint32_t events_;
    uint32_t revents_;
    EventCallback eventCallback_;
    EventLoop *eventLoopOwner_;
    void *eventData_;
};

} // namespace cppevt

#endif