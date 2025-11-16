cmake_minimum_required(VERSION 3.29)
project(task1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(task1
    company.cpp
    company.h
    employee.cpp
    employee.h
    listTemp.h
    main.cpp)
