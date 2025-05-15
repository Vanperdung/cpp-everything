#include <net/iomonitor/Poll.h>

using namespace cppevt;

Poll::Poll()
{
}

Poll::~Poll()
{
}


Timestamp Poll::poll(int timeoutMs, ChannelList *activeChannels)
{
    
}

status_t Poll::addChannel(Channel *channel)
{
    return CPPEVT_OK;
}

status_t Poll::modifyChannel(Channel *channel)
{
    return CPPEVT_OK;
}

status_t Poll::deleteChannel(Channel *channel)
{
    return CPPEVT_OK;
}