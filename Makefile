LIBFT = ./42-libft/libft.a

CFLAGS = -I./includes #-Wall -Werror -Wextra
NAME = cube3d


SRC = ./src/main.c ./src/parser/parser_utils.c ./src/error.c \
		./src/parser/parser.c


CC = gcc

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(MAKE) -C ./libft
		$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJ) ./libft/libft.a

%.o: %.c
		gcc  $(CFLAGS) -c $< -o $@

clean:
		$(MAKE) clean -C ./libft
		rm -rf $(OBJ)

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -rf $(NAME)
re: fclean all

.PHONY:	all clean fclean re