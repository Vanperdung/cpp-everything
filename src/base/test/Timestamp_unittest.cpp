#include <base/Timestamp.h>

#include <iostream>

int main(int argc, char *argv[])
{
    cppevt::Timestamp timestamp;
    timestamp.now();

    std::cout << timestamp.toString() << std::endl;

    return 0;
}