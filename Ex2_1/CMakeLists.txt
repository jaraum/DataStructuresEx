cmake_minimum_required(VERSION 4.2)
project(Ex2_1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Ex2_1 main.c
        bt.c
        bt.h)
