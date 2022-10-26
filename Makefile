NAME := minishell
LIBFT_PATH := ./libft/
LIBFT = $(LIBFT_PATH)libft.a
READLINE_LIB :=  -L /Users/$(USER)/.brew/opt/readline/lib -lreadline
READLINE_INC := -I /Users/$(USER)/.brew/opt/readline/include
FLAGS := -Wall -Werror -Wextra
#FLAGS += -fsanitize=address -g3

SRCS := srcs/main.c \
		srcs/parsing/parse_redirecs.c \
		srcs/parsing/heredoc.c \
		srcs/parsing/utils_heredoc.c \
		srcs/parsing/utils.c \
		srcs/parsing/quotes.c \
		srcs/parsing/dollars.c \
		srcs/parsing/check_cmdline.c \
		srcs/parsing/utils_check_cmdline.c \
		srcs/signals/signal_handler.c \
		srcs/parsing/utils_targmode_arrays.c \
		srcs/exec/exec_hub.c \
		srcs/exec/env_checker.c \
		srcs/exec/pipex_utils.c \
		srcs/exec/exec_process.c \
		srcs/exec/fork_process.c \
		srcs/exec/sorting_hub.c \
		srcs/exec/process_pipe.c \
		srcs/utils/init.c \
		srcs/exec/cd_exec.c \
		srcs/exec/env_exec.c \
		srcs/exec/export_exec.c \
		srcs/exec/unset_exec.c \
		srcs/exec/built_ins_utils.c \
		srcs/built-ins/exit.c \
		srcs/built-ins/echo.c \
		srcs/built-ins/pwd.c \
		srcs/exec/set_redirection.c \
		srcs/exec/exec_utils.c \
		srcs/exec/process_pipe_built_in.c \
		srcs/exec/cd_utils.c\


OBJS := $(SRCS:.c=.o)

all: libftmake $(NAME)

%.o: %.c incs/minishell.h Makefile $(LIBFT)
	@gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS) Makefile
	@gcc $(LIBFT) $(READLINE_LIB) $(FLAGS) $(READLINE_INC) $(OBJS) -L $(LIBFT_PATH) -lft -o $(NAME)
	@echo "Conchito:\t\033[1;32m[READY TO USE]\033[0m"
	@echo "You can launch it with: \033[7m./minishell\033[0m\n"

clean:
	@rm -rf $(OBJS)
	@echo "The Conchito's house is cleaned up now!"

fclean: clean libftclean
	@rm -rf $(NAME)

libftmake:
	@make -C libft

libftclean:
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean libftmake libftclean re
