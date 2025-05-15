#include <base/UtcTime.h>

#include <iostream>

int main(int argc, char *argv[])
{
    cppevt::UtcTime utcTime;
    utcTime.now();

    std::cout << utcTime.toString() << std::endl;

    return 0;
}