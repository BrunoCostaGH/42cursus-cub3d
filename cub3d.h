/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:14:41 by tabreia-          #+#    #+#             */
/*   Updated: 2023/07/06 15:07:29 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	int		player;
	char	**map_arr;
	char	**map_val;
	t_point	map_size;
}	t_map;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
}	t_img;

typedef struct s_file
{
	char	**txt;
	char	**textures;
	int		**colors;
	char	**map_arr;
}	t_file;

typedef struct s_player
{
	t_point	init_pos;
	char	init_dir;
}	t_player;


typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			map_sur;
	t_point		flood_point;
	t_point		max;
	t_point		window;
	t_player	player;
	t_file		*file_cont;
	t_img		img;
	t_map		map;
}	t_data;

bool	check_if_file_exists(char *file_path, int is_cub_file);
bool	valid_cub_file(char *file_path, t_data *data);
bool	is_valid_char(char c, bool for_player);

int		get_init_player_pos(t_data *data, char **map, int y);
int		read_file(char *file_path, t_data *data);

char	**check_for_data(char **str, t_data *data);
char	**get_map(int beg_map, char **txt);

void	start_game(t_data *data);

#endif
