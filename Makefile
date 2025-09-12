# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 21:59:37 by fares-_-q7h       #+#    #+#              #
#    Updated: 2025/09/11 22:03:42 by fares-_-q7h      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	pipx
SRC = main.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
CC = cc
LIBFT_DIR = libftprintf
LIBFT_EXE = $(LIBFT_DIR)/libftprintf.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_EXE)
	cc $(OBJ) $(LIBFT_EXE) -o $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(LIBFT_EXE):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f *.o
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f *.o
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all