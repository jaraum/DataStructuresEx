cmake_minimum_required(VERSION 4.2)
project(dsEx C)

set(CMAKE_C_STANDARD 11)

include_directories(Ex1_1)
include_directories(Ex1_2)
include_directories(Ex1_3)

add_executable(dsEx
        Ex1_1/main.c
        Ex1_1/SeqList.c
        Ex1_1/SeqList.h
        Ex1_2/LinkList.c
        Ex1_2/LinkList.h
        Ex1_2/main.c
        Ex1_3/main.c
        Ex1_3/polynomial.c
        Ex1_3/polynomial.h)
