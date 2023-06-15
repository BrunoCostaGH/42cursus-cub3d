CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -L ./minilibx-linux -lm -lmlx -Ilmlx -lXext -lX11
DEPS = minilibx-linux/libmlx.a libft/libft.a
NAME = cub3d
SRC = handle_file.c inits.c main.c validate_file.c
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: deps $(NAME)
deps:
	$(MAKE) -C ./libft
	#$(MAKE) -C ./minilibx-linux
$(NAME): $(OBJ) $(DEPS)
	$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) $(LIBFT) -o $(NAME)
clean:
	$(MAKE) $@ -C ./libft
	#$(MAKE) $@ -C ./minilibx-linux
	@rm -rf $(OBJ) $(BONUS_OBJ)
fclean: clean
	$(MAKE) $@ -C ./libft
	@rm -rf $(NAME) $(BONUS_NAME)
re: fclean all