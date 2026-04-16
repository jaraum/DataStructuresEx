cmake_minimum_required(VERSION 4.2)
project(Ex1_3 C)

set(CMAKE_C_STANDARD 11)

add_executable(Ex1_3 main.c
        polynomial.c
        polynomial.h)
