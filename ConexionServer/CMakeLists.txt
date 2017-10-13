cmake_minimum_required(VERSION 3.8)
project(ConexionServer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp server/request.cpp server/request.h)
add_executable(ConexionServer ${SOURCE_FILES})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")