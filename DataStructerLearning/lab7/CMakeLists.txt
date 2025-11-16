cmake_minimum_required(VERSION 3.30)
project(lab7)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(lab7
        src/networkmain.cpp
        src/network.h
        src/network.cpp)
