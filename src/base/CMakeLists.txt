set(base_SRCS
    Timestamp.cpp
    PThreadMutex.cpp
    PThread.cpp
)

add_library(cppevt_base ${base_SRCS})
add_subdirectory(test)