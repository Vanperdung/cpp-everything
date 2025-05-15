#include <net/iomonitor/Epoll.h>

#include <string>
#include <stdexcept>
#include <cstring>
#include <cerrno>
#include <iostream>

#include <string.h>

#include <unistd.h>

using namespace cppevt;

Epoll::Epoll()
{
    epollfd_ = ::epoll_create1(0);
    if (epollfd_ < 0)
        throw std::runtime_error(std::strerror(errno));

    events_.empty();
    events_.resize(kMaxEvent);
}

Epoll::~Epoll()
{
    if (epollfd_ > 0)
        ::close(epollfd_);
}

/**
 * @brief Wait for events on an epoll instance
 *
 * @param[in] timeoutMs The maximum wait time in milliseconds (-1 == infinite) 
 * @param[in,out] activeChannels Stores all of active channels which are triggered
 * by poll() 
 */
Timestamp Epoll::poll(int timeoutMs, ChannelList *activeChannels)
{
    Timestamp triggerTime;

    events_.empty();

    int numEvents = ::epoll_wait(epollfd_,
                                &events_[0],
                                static_cast<int>(events_.size()),
                                timeoutMs);
    
    triggerTime.now();

    if (numEvents > 0)
        fillActiveChannels(numEvents, activeChannels);
    else if (numEvents == 0)
        std::cout << "Epoll::poll(): nothing happened" << std::endl;
    else 
        std::cerr << "Epoll::poll(): " << std::strerror(errno) << std::endl;

    return triggerTime;
}

status_t Epoll::addChannel(Channel *channel)
{
    int fd = channel->fd();

    std::map<int, Channel*>::iterator it = channels_.find(fd);
    if (it != channels_.end())
    {
        std::cerr << "FD existed, FD=" << fd << std::endl;
        return CPPEVT_NOT_FOUND;
    }

    if (channels_.size() >= kMaxEvent)
    {
        std::cerr << "Exceed the number of supported channels" << std::endl;
        return CPPEVT_EXCEED_RANGE;
    }

    channels_[fd] = channel;
    update(EPOLL_CTL_ADD, channel);

    return CPPEVT_OK;
}

status_t Epoll::modifyChannel(Channel *channel)
{
    int fd = channel->fd();

    std::map<int, Channel*>::iterator it = channels_.find(fd);
    if (it != channels_.end())
    {
        std::cerr << "FD existed, FD=" << fd << std::endl;
        return CPPEVT_NOT_FOUND;
    }

    update(EPOLL_CTL_MOD, channel);

    return CPPEVT_OK;
}

status_t Epoll::deleteChannel(Channel *channel)
{
    int fd = channel->fd();

    std::map<int, Channel*>::iterator it = channels_.find(fd);
    if (it != channels_.end())
    {
        std::cerr << "FD existed, FD=" << fd << std::endl;
        return CPPEVT_NOT_FOUND;
    }

    update(EPOLL_CTL_DEL, channel);
    channels_.erase(fd);

    return CPPEVT_OK;
}

void Epoll::update(int operation, Channel *channel)
{
    struct epoll_event ev;

    memset(&ev, 0, sizeof(ev));
    ev.events = channel->events();
    ev.data.ptr = channel;
    int fd = channel->fd();

    int ret = ::epoll_ctl(epollfd_, operation, fd, &ev);
    if (ret < 0)
        throw std::runtime_error(std::string("epoll_ctl(): ") + std::strerror(errno));
}

void Epoll::fillActiveChannels(int numEvents, ChannelList *activeChannels)
{
    for (int i = 0; i < numEvents; i++)
    {
        Channel *channel = static_cast<Channel*>(events_[i].data.ptr);

        // Save the returned events by epoll_wait to activeChannels
        // Channel object uses returned events to call the correct cb handler
        channel->set_revents(events_[i].events);
        activeChannels->push_back(channel);
    }
}