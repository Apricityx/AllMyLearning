cmake_minimum_required(VERSION 3.10)

project(Chapter2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(ch2 src/main.cpp src/instance/factorial.cpp
        src/instance/reverse_string.cpp)
