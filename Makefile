LIBFT = ./42-libft/libft.a

CFLAGS = -ggdb3  -I./includes #-Wall -Werror -Wextra
NAME = cube3d


SRC = ./src/main.c ./src/parser/parser_utils.c ./src/error.c \
		./src/parser/parser.c


CC = gcc

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(MAKE) -C ./42-libft
		$(CC) -o $(NAME) $(OBJ) ./42-libft/libft.a

%.o: %.c
		gcc $(CFLAGS) -c $< -o $@

clean:
		$(MAKE) clean -C ./42-libft
		rm -rf $(OBJ)

fclean: clean
		$(MAKE) fclean -C ./42-libft
		rm -rf $(NAME)
re: fclean all

.PHONY:	all clean fclean re