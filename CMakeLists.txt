cmake_minimum_required(VERSION 3.20)
project(Minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(.libft ./srcs/built-ins)

file(GLOB minishell_SRC CONFIGURE_DEPENDS "*.h" "*.c")

add_executable(Minishell
        ${minishell_SRC} srcs/utils/init.c
        srcs/parsing/nigga-tests.c
        srcs/parsing/utils.c
        srcs/parsing/heredoc.c
        srcs/parsing/parse_redirecs.c
        srcs/built-ins/echo.c
        Makefile.linux
        Makefile srcs/parsing/utils_heredoc.c srcs/parsing/quotes.c srcs/parsing/dollars.c srcs/parsing/check_cmdline.c srcs/parsing/utils_check_cmdline.c)
