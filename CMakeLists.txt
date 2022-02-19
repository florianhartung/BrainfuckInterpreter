cmake_minimum_required(VERSION 3.19)
project(BrainfuckInterpreter C)

set(CMAKE_C_STANDARD 99)

add_executable(BrainfuckInterpreter src/main.c src/include/bfinterpreter.h src/bfinterpreter.c)