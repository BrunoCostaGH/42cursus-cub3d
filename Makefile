# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 22:20:44 by tabreia-          #+#    #+#              #
#    Updated: 2023/08/09 18:16:16 by bsilva-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -L ./minilibx-linux -lm -lmlx -Ilmlx -lXext -lX11
DEPS = minilibx-linux/libmlx.a libft/libft.a
NAME = cub3d

BASE_DIR = source_base
SRC_BASE = $(BASE_DIR)/draw.c $(BASE_DIR)/draw2.c $(BASE_DIR)/err_msg.c \
$(BASE_DIR)/err_msg2.c $(BASE_DIR)/free.c $(BASE_DIR)/game.c \
$(BASE_DIR)/handle_file.c $(BASE_DIR)/handle_file_utils.c \
$(BASE_DIR)/handle_file_utils2.c $(BASE_DIR)/handle_input.c \
$(BASE_DIR)/inits.c $(BASE_DIR)/move.c $(BASE_DIR)/raycast.c \
$(BASE_DIR)/rotate.c $(BASE_DIR)/set_dir_vector.c $(BASE_DIR)/textures.c \
$(BASE_DIR)/validate_file.c $(BASE_DIR)/validate_file_utils.c main.c
OBJ_BASE = $(SRC_BASE:.c=.o)

LIBFT = libft/libft.a

all: deps $(NAME)
deps:
	$(MAKE) -C ./libft
	#$(MAKE) -C ./minilibx-linux
$(NAME): $(OBJ_BASE) $(DEPS)
	$(CC) $(CFLAGS) $(OBJ_BASE) $(MLXFLAGS) $(LIBFT) -o $(NAME)
clean:
	$(MAKE) $@ -C ./libft
	#$(MAKE) $@ -C ./minilibx-linux
	@rm -rf $(OBJ_BASE)
fclean: clean
	$(MAKE) $@ -C ./libft
	@rm -rf $(NAME)
re: fclean all
