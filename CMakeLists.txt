cmake_minimum_required(VERSION 3.20)
project(Minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(. libft ./srcs/built-ins)

add_executable(Minishell
        incs/minishell.h
        srcs/parsing/nigga-tests.c srcs/signals/signal_handler.c
        srcs/parsing/parse_redirecs.c
        a.out srcs/built-ins/echo.c libft/libft.a libft/libft.h
        srcs/built-ins/pwd.c srcs/built-ins/exit.c
        GNL/get_next_line_bonus.c srcs/parsing/heredoc.c srcs/parsing/utils.c)
