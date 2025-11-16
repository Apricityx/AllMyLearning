cmake_minimum_required(VERSION 3.29)
project(Traceback)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
include_directories(task1)

add_executable(Traceback
        task1/backtrack.cpp
        task1/backtrack.h
        task1/main.cpp
        task1/position.h
        task1/position.cpp
        task1/application.cpp
        task1/application.h)
