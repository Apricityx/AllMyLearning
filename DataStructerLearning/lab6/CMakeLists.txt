cmake_minimum_required(VERSION 3.30)
project(lab6)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(lab6
        src/main.cpp
        src/bst.h)
