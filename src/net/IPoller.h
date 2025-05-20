#ifndef __IPOLLER_H__
#define __IPOLLER_H__

#include <net/Channel.h>

#include <base/NonCopyable.h>
#include <base/Types.h>
#include <base/Timestamp.h>

#include <map>
#include <list>

namespace cppevt 
{

class Channel;

class IPoller : private NonCopyable
{
public:
    virtual ~IPoller() = default;

    typedef std::list<Channel*> ChannelList;

    virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) = 0;

    virtual status_t addChannel(Channel *channel) = 0;
    virtual status_t modifyChannel(Channel *channel) = 0;
    virtual status_t deleteChannel(Channel *channel) = 0;

    virtual void detachAllChannels() = 0;

protected:
    std::map<int, Channel*> channels_;
};

} // namespace cppevt

#endif