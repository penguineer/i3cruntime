cmake_minimum_required(VERSION 2.8.9)

project (CRC)

set(CMAKE_C_FLAGS "-std=c99")


add_executable(i3cmaster master.c)
