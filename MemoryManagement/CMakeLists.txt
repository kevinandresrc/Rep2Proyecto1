cmake_minimum_required(VERSION 3.8)
project(MemoryManagement)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp DS/file.cpp DS/file.h DS/node.cpp)
add_executable(MemoryManagement ${SOURCE_FILES} DS/file.cpp DS/file.h)