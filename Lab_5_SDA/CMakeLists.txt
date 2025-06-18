cmake_minimum_required(VERSION 3.30)
project(Lab_5_SDA C)

set(CMAKE_C_STANDARD 23)

add_executable(Lab_5_SDA main.c
        functions.c
        functions.h
        structs.h)
