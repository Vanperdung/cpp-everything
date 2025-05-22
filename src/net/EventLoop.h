#ifndef __EVENT_LOOP_H__
#define __EVENT_LOOP_H__

#include <net/IPoller.h>
#include <net/Channel.h>

#include <base/NonCopyable.h>
#include <base/Types.h>
#include <base/Timestamp.h>

#include <memory>
#include <vector>
#include <list>

namespace cppevt
{

class Channel;
class IPoller;

class EventLoop : private NonCopyable
{
public:
    EventLoop();
    ~EventLoop();

    typedef std::list<Channel*> ChannelList;

    status_t newPoll();
    status_t newEpoll();

    status_t addChannel(Channel *channel);
    status_t modifyChannel(Channel *channel);
    status_t deleteChannel(Channel *channel); 
    
    void loop(int timeoutMs);

private:
    std::unique_ptr<IPoller> poller_;
    ChannelList activeChannels_;
    bool quit_ = false;
};

} // namespace cppevt

#endif