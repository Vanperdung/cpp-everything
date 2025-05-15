cmake_minimum_required(VERSION 3.10)

project(cpp-everything)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")

add_subdirectory(src)