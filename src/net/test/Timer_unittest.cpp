#include <net/Timer.h>

#include <iostream>
#include <stdexcept>

#include <sys/epoll.h>
#include <unistd.h>

void timerCallback(void)
{
    std::cout << "In timer callback" << std::endl;
}

int main(int argc, char *argv[])
{
    try
    {
        cppevt::Timestamp expiration, interval(2, 0);
        expiration.now();
        expiration = expiration + interval;

        cppevt::Timer timer;
        timer.create();
        timer.set(expiration, interval);
        timer.setCallback(timerCallback);

        cppevt::EventLoop eventLoop;
        eventLoop.newEpoll();
        eventLoop.addChannel(timer.channel());

        eventLoop.loop(-1);
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}