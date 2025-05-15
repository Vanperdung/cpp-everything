set(net_SRCS
    Timer.cpp
    Channel.cpp
    EventLoop.cpp
    iomonitor/Epoll.cpp
    iomonitor/Poll.cpp
)

add_library(cppevt_net ${net_SRCS})
target_link_libraries(cppevt_net cppevt_base)

add_subdirectory(test)