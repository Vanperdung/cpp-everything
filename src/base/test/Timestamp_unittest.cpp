#include <base/Timestamp.h>

#include <iostream>

int main(int argc, char *argv[])
{
    cppevt::Timestamp Timestamp;
    Timestamp.now();

    std::cout << Timestamp.toString() << std::endl;

    return 0;
}