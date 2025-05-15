#include <net/EventLoop.h>
#include <net/iomonitor/Poll.h>
#include <net/iomonitor/Epoll.h>

#include <iostream>
#include <stdexcept>

using namespace cppevt;

EventLoop::EventLoop()
{
}

EventLoop::~EventLoop()
{
}

status_t EventLoop::newPoll()
{
    if (poller_)
    {
        std::cerr << "EventLoop had Poller object" << std::endl;
        return CPPEVT_ERROR;
    }

    poller_ = std::make_unique<Poll>();
    return CPPEVT_OK;
}

status_t EventLoop::newEpoll()
{
    if (poller_)
    {
        std::cerr << "EventLoop had Poller object" << std::endl;
        return CPPEVT_ERROR;
    }

    poller_ = std::make_unique<Epoll>();
    return CPPEVT_OK;
}

status_t EventLoop::addChannel(Channel *channel)
{
    channel->setEventLoopOwner(this);
    return poller_->addChannel(channel);
}

status_t EventLoop::modifyChannel(Channel *channel)
{
    return poller_->modifyChannel(channel);
}

status_t EventLoop::deleteChannel(Channel *channel)
{
    channel->setEventLoopOwner(NULL);
    return poller_->deleteChannel(channel);
}

void EventLoop::loop(int timeoutMs)
{
    quit_ = false;

    while (!quit_)
    {
        activeChannels_.clear();

        if (!poller_)
            throw std::runtime_error("Missing Poller for EventLoop");

        poller_->poll(timeoutMs, &activeChannels_);
        for (Channel *channel : activeChannels_)
        {
            channel->callEventCallback();
        }
    }
}