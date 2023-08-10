/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:14:41 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/10 15:52:56 by bsilva-c         ###   ########.fr       */
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

typedef struct t_vector
{
	double			x;
	double			y;
}	t_vector;
typedef struct s_point
{
	int				x;
	int				y;
}	t_point;

typedef struct s_moves
{
	bool	forward;
	bool	back;
	bool	right;
	bool	left;
	bool	r_right;
	bool	r_left;
}	t_moves;

typedef struct s_img
{
	void			*mlx_img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}	t_img;

typedef struct s_file
{
	char			**txt;
	char			**textures_path;
	int				**colors;
	char			**map_arr;
	t_point			map_size;
}	t_file;

typedef struct s_player
{
	t_point			init_pos;
	char			init_dir;
}	t_player;

typedef struct s_ray
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				side;
	int				hit;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				color;
}	t_ray;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				id;
	double			draw_mid_point;
	t_vector		window;
	t_player		player;
	t_file			*file_cont;
	t_img			*img;
	t_img			**tex_img;
	t_ray			ray;
	t_moves			moves;
}	t_data;

bool			is_valid_char(char c, bool for_player);
bool			valid_cub_file(char *file_path, t_data *data);
bool			check_if_file_exists(char *file_path, int is_cub_file);
bool			is_valid_struct(t_data *data);
bool			is_empty_line(char *str);

int				raycast(t_data *v_data);
int				free_game(t_data *data);
int				handle_movement(t_data *data);
int				handle_keypress(int key, t_data *data);
int				encode_rgb(int red, int green, int blue);
int				read_file(char *file_path, t_data *data);
int				handle_key_release(int key, t_data *data);
int				find_identifiers(char **str, t_data *data);
int				run_compares(char *str, t_data *data);
int				save_rgb_to_struct(char *str, int id, t_data *data);
int				save_path_to_struct(char *str, int id, t_data *data);
int				get_init_player_pos(t_data *data, char **map, int y);
int				check_rgb_range(char **rgb);
int				validate_rgb(t_data *data, int id, char **info, char **rgb);

unsigned int	gix(t_img *img, int x, int y);

char			**get_map(int beg_map, char **txt);
char			**check_for_data(char **str, t_data *data);

void			set_n(t_data *data);
void			set_s(t_data *data);
void			set_e(t_data *data);
void			set_w(t_data *data);
void			draw_floor(t_data *data);
void			start_game(t_data *data);
void			free_int_arr(int **info);
void			init_moves(t_data *data);
void			free_file_cont(t_data *data);
void			free_char_arr(char **info);
void			init_images(t_data *data);
void			draw_ceiling(t_data *data);
void			load_textures(t_data *data);
void			texture_picker(t_data *data);
void			init_file_cont(t_data *data);
void			get_dir_vector(t_data *data);
void			init_image(t_data *data, t_img *image);
void			pix(t_img *img, int x, int y, int color);
void			write_empty_file(char *file_path);
void			write_invalid_format_path(char **info);
void			write_out_of_range(char **info, char **rgb);
void			write_miss_rgb(char **info, char **rgb);
void			write_invalid_format_rgb(char **info);
void			copy_file_path(t_data *data, char **info, int len, int id);
void			save_values(t_data *data, int id, char **rgb, char **info);
void			apply_texture(t_data *data, int x, int id);
void			move_forward(t_data *info, double move_speed);
void			move_backwards(t_data *info, double move_speed);
void			move_left(t_data *info, double move_speed);
void			move_right(t_data *info, double move_speed);
void			rotate_left(t_data *info, double rot_speed);
void			rotate_right(t_data *info, double rot_speed);
void			draw_vert_line(t_img *img, t_point draw_start, \
				t_point draw_end, int color);
#endif
