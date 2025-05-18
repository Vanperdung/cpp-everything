#ifndef __POLL_H__
#define __POLL_H__

#include <net/IPoller.h>
#include <net/Channel.h>

#include <base/Types.h>
#include <base/Timestamp.h>

namespace cppevt
{

class Poll : public IPoller
{
public:
    Poll();
    ~Poll();

    typedef std::list<Channel*> ChannelList;

    Timestamp poll(int timeoutMs, ChannelList *activeChannels) override;

    status_t addChannel(Channel *channel) override;
    status_t modifyChannel(Channel *channel) override;
    status_t deleteChannel(Channel *channel) override;

private:
    
};

} // namespace cppevt

#endif