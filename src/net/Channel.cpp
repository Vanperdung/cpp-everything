#include <net/Channel.h>

using namespace cppevt;

Channel::Channel(int fd)
    : fd_(fd),
    events_(0),
    revents_(0)
{
}

Channel::~Channel()
{
}

void Channel::set_events(uint32_t events)
{
    events_ = events;
}

void Channel::set_revents(uint32_t revents)
{
    revents_ = revents;
}

void Channel::setEventCallback(const EventCallback &cb)
{
    eventCallback_ = cb;
}

void Channel::callEventCallback()
{
    eventCallback_(revents_, eventData_);
}

void Channel::setEventLoopOwner(EventLoop *owner)
{
    eventLoopOwner_ = owner;
}

EventLoop* Channel::getEventLoopOwner()
{
    return eventLoopOwner_;
}

void Channel::setEventData(void *data)
{
    eventData_ = data;
}