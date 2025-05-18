#include <base/Types.h>
#include <net/EventLoop.h>
#include <net/Channel.h>

#include <iostream>
#include <stdexcept>

#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

void callback(uint32_t revents, void *data)
{
    if (revents & EPOLLIN)
    {
        std::cout << "Receive event EPOLLIN" << std::endl;
        char buf[1024];
        ssize_t n;
        while ((n = read(*(int*)data, buf, sizeof(buf))) > 0)
        {
            std::cout << "Read " << n << " bytes: " << std::string(buf, n) << std::endl;
        }
    }
}

int main(int argc, char *argv[])
{
    int *sv = new int[2]; // sv[0] for reading, sv[1] for writing
    try
    {
        if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) < 0) 
            throw std::runtime_error("Cannot open file");
        
        cppevt::Channel fileChannel(sv[0]);
        fileChannel.set_events(EPOLLIN | EPOLLET);
        fileChannel.setEventCallback(callback);
        fileChannel.setEventData(&sv[0]);

        cppevt::EventLoop eventLoop;
        if (eventLoop.newEpoll() != CPPEVT_OK)
            throw std::runtime_error("Cannot create Epoll");
        
        if (eventLoop.addChannel(&fileChannel) != CPPEVT_OK)
            throw std::runtime_error("Cannot add channel");
        
        // Write some data to trigger EPOLLIN
        const char* msg = "hello";
        write(sv[1], msg, 5);
        
        eventLoop.loop(200);
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
    }

    close(sv[0]);
    close(sv[1]);

    delete[] sv;
    return 0;
}