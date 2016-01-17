cmake_minimum_required(VERSION 2.8.9)

project (I3CMASTER)

set(CMAKE_C_FLAGS "-std=c++14")


add_executable(i3cmaster master.cpp)
