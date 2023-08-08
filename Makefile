# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 22:20:44 by tabreia-          #+#    #+#              #
#    Updated: 2023/07/06 15:06:09 by bsilva-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -L ./minilibx-linux -lm -lmlx -Ilmlx -lXext -lX11
DEPS = minilibx-linux/libmlx.a libft/libft.a
NAME = cub3d
SRC = handle_file.c inits.c main.c validate_file.c validate_file_utils.c game.c \
	draw.c draw2.c free.c handle_file_utils.c handle_input.c move.c raycast.c \
	rotate.c set_dir_vector.c textures.c
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
