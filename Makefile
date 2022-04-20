NAME := minishell
LIBFT_PATH := ./libft/
LIBFT := $(LIBFT_PATH)libft.a
READLINE_LIB := -lreadline -L $(shell brew --prefix readline)/lib
READLINE_INC := -I $(shell brew --prefix readline)/include
FLAGS := -Wall -Werror -Wextra

SRCS := nigga-tests.c

OBJS := $(SRCS:.c=.o)

all: libftmake $(NAME)

%.o:%.c minishell.h Makefile $(LIBFT)
	gcc -c $< -o $@

$(NAME): $(OBJS)
	gcc $(LIBFT) $(READLINE_LIB) $(READLINE_INC) $(OBJS) -o $(NAME)

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
