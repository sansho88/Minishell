cmake_minimum_required(VERSION 3.20)
project(Minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Minishell
        nigga-tests.c minishell.h)
