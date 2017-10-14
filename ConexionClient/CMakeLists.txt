cmake_minimum_required(VERSION 3.8)
project(ConexionClient)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp client/rmlib.cpp client/rmlib.h)
##add_executable(ConexionClient ${SOURCE_FILES})
add_executable(ConexionClient ${SOURCE_FILES} client/request.cpp client/request.h client/rmlib.cpp client/rmlib.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")