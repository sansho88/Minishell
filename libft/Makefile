# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2021/11/10 17:13:35 by tgriffit          #+#    #+#             #
#   Updated: 202#    Updated: 2022/04/19 18:05:26 by tgriffit         ###   ########.fr        #
                                                           #
# ************************************************************************** #

NAME = libft.a

CC = @gcc
CFLAGS = -Wall -Wextra -Werror
AR =  @ar rcs
RM = @rm -f
HEADER = ./includes/

SRCS = ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_split_len.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_striteri.c

SRCS_BONUS = 	ft_lstnew.c \
	  		ft_lstadd_front.c \
	  		ft_lstsize.c \
	  		ft_lstlast.c \
	  		ft_lstadd_back.c \
	  		ft_lstdelone.c \
	  		ft_lstclear.c \
	  		ft_lstiter.c \
	  		ft_lstmap.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
	@echo "Libft is ready now!"

bonus: $(NAME) $(OBJS_BONUS)
	$(AR) $(NAME) $(OBJS_BONUS)
	@echo "All bonus are included now!"

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	@echo "Clean!"

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re bonus