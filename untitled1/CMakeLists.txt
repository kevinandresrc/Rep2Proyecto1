cmake_minimum_required(VERSION 3.8)
project(untitled1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp client/rmlib.cpp client/rmlib.h client/request.cpp client/request.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
add_executable(untitled1 ${SOURCE_FILES})