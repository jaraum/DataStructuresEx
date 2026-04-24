cmake_minimum_required(VERSION 4.2)
project(Ex1_3_HEAD C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Ex1_3_HEAD
        LinkedList.c
        LinkedList.h
        main.c)
