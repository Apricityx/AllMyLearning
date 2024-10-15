cmake_minimum_required(VERSION 3.29)
project(part0)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(part0
        arrayCont.h
        company.cpp
        company.h
        employee.cpp
        employee.h
        main.cpp)
