cmake_minimum_required(VERSION 3.20)
project(Minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Minishell
        incs/minishell.h "srcs/parsing/nigga-tests.c" srcs/signals/signal_handler.c
        srcs/parsing/parse_redirecs.c)
