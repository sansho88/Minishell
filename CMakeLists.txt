cmake_minimum_required(VERSION 3.20)
project(Minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(.libft ./srcs/built-ins)

file(GLOB minishell_SRC CONFIGURE_DEPENDS "*.h" "*.c")

add_executable(Minishell
        ${minishell_SRC} srcs/utils/init.c
        srcs/parsing/nigga-tests.c
        srcs/utils
        srcs/parsing/utils.c
        Makefile.linux
        Makefile)
