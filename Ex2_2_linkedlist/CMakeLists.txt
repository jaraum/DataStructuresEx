cmake_minimum_required(VERSION 4.2)
project(Ex2_2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Ex2_2
        hfmTree.c
        hfmTree.h
        main.c)
