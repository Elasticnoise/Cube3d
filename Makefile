LIBFT = ./libft/libft.a

CFLAGS = -I./includes #-Wall -Werror -Wextra
NAME = cube3d


SRC = ./src/main.c ./src/parser/parser_utils.c ./src/error.c \
		./src/parser/parser.c \
		./src/keycode_actions.c \
		./src/keycode_actions_check.c \
		./src/render/draw.c \
		./srs/render/raycaster.c \
		./src/render/raycaster2.c \
		./src/render/set_color.c \
		./src/render/set_deg.c \
		./src/render/set_wall. c \


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