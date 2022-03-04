LIBFT = ./libft/libft.a

CFLAGS = -I./includes #-Wall -Werror -Wextra
NAME = cube3d


SRC = ./src/main.c ./src/parser/parser_utils.c ./src/error.c \
		./src/parser/parser.c \
		./src/render/init_colors.c \
		./src/render/key_move.c \
		./src/render/key_move_2.c \
		./src/keycode_actions.c \
		./src/keycode_actions_check.c \


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