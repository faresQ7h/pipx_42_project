NAME = 	libftprintf.a
SRC = ft_printf.c continue_printf.c ft_utoa.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
CC = cc
LIBFT_DIR = libft
LIBFT_EXE = $(LIBFT_DIR)/libft.a

.PHONY: all clean fclean re

all: $(NAME) $(LIBFT_EXE)

$(NAME): $(OBJ) $(LIBFT_EXE)
	ar rcs $(NAME) $(LIBFT_DIR)/*.o $(OBJ)

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