cmake_minimum_required(VERSION 3.9)
project(fms C)

set(CMAKE_C_STANDARD 99)

add_executable(fms main.c fms.c fms.h)