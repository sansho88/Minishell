NAME := minishell
LIBFT_PATH := ./libft/
LIBFT := $(LIBFT_PATH)libft.a
READLINE_LIB := -lreadline -L $(shell brew --prefix readline)/lib
READLINE_INC := -I $(shell brew --prefix readline)/include
FLAGS := -Wall -Werror -Wextra -fsanitize=address -g3

SRCS := srcs/parsing/nigga-tests.c \
		srcs/parsing/parse_redirecs.c \
		srcs/exec/pipex.c \
		srcs/exec/fork_process.c \
		srcs/exec/ft_split.c \
		srcs/exec/pipe_process.c \
		srcs/exec/pipex_utils.c \
		srcs/exec/utils.c \

OBJS := $(SRCS:.c=.o)

all: libftmake $(NAME)

%.o:%.c minishell.h Makefile $(LIBFT)
	gcc -c $< -fsanitize=address -g3  -o $@

$(NAME): $(OBJS)
	gcc $(LIBFT) $(READLINE_LIB) $(READLINE_INC) $(OBJS) -fsanitize=address -g3  -o $(NAME)

clean:
	rm $(OBJS)

fclean: clean libftclean
	rm $(NAME)

libftmake:
	make -C libft

libftclean:
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean libftmake libftclean re