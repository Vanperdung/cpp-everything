#ifndef __EPOLL_H__
#define __EPOLL_H__

#include <net/IPoller.h>
#include <net/Channel.h>

#include <base/Types.h>

#include <vector>
#include <list>

#include <sys/epoll.h>

namespace cppevt
{

class Epoll : public IPoller
{
public:
    Epoll();
    ~Epoll();

    typedef std::list<Channel*> ChannelList;

    Timestamp poll(int timeoutMs, ChannelList *activeChannels) override;

    status_t addChannel(Channel *channel) override;
    status_t modifyChannel(Channel *channel) override;
    status_t deleteChannel(Channel *channel) override;

    void detachAllChannels() override;

private:
    void update(int operation, Channel *channel);
    void fillActiveChannels(int numEvents, ChannelList *activeChannels); 

    int epollfd_;
    std::vector<struct epoll_event> events_;
    static const int kMaxEvent = 32;
};

} // namespace cppevt

#endif