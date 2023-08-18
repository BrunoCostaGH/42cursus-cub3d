/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 21:11:42 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/08/10 17:52:23 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"

static void	get_fov_line_max(t_data *data)
{
	if (data->ray.side == 0)
	{
		data->max_fov_dec = data->ray.pos_y + \
					data->ray.perp_wall_dist * data->ray.ray_dir_y;
		data->max_fov_dec -= data->ray.map_y;
	}
	else
	{
		data->max_fov_dec = data->ray.pos_x + \
					data->ray.perp_wall_dist * data->ray.ray_dir_x;
		data->max_fov_dec -= data->ray.map_x;
	}
	data->max_fov_hp.x = data->ray.map_x;
	data->max_fov_hp.y = data->ray.map_y;
}

static void	get_fov_line_min(t_data *data)
{
	if (data->ray.side == 0)
	{
		data->min_fov_dec = data->ray.pos_y + \
					data->ray.perp_wall_dist * data->ray.ray_dir_y;
		data->min_fov_dec -= data->ray.map_y;
	}
	else
	{
		data->min_fov_dec = data->ray.pos_x + \
					data->ray.perp_wall_dist * data->ray.ray_dir_x;
		data->min_fov_dec -= data->ray.map_x;
	}
	data->min_fov_hp.x = data->ray.map_x;
	data->min_fov_hp.y = data->ray.map_y;
}

void	get_fov_line(t_data *data, int x)
{
	if (x == 1)
	{
		get_fov_line_min(data);
	}
	else if (x == data->window.x - 1)
	{
		get_fov_line_max(data);
	}
}

static void	draw_map(t_data *data, int multiplier, int color[2])
{
	int		x;
	int		y;
	t_point	player;
	t_point	hp;

	player.x = data->ray.pos_x * multiplier;
	player.y = data->ray.pos_y * multiplier;
	hp.x = (data->min_fov_hp.x * multiplier) + (data->min_fov_dec * multiplier);
	hp.y = (data->min_fov_hp.y * multiplier) + (data->min_fov_dec * multiplier);
	draw_line(data, player, hp);
	hp.x = (data->max_fov_hp.x * multiplier) + (data->max_fov_dec * multiplier);
	hp.y = (data->max_fov_hp.y * multiplier) + (data->max_fov_dec * multiplier);
	draw_line(data, player, hp);
	y = 0;
	while (data->file_cont->map_arr[++y - 1])
	{
		x = 0;
		while (data->file_cont->map_arr[y - 1][++x - 1])
			if (data->file_cont->map_arr[y - 1][x - 1] == '1')
				draw_square(data, (y - 1) * multiplier, (x - 1) * multiplier, \
					color[0]);
	}
	draw_square_player(data, ((data->ray.pos_y) * multiplier) - 3, \
		((data->ray.pos_x) * multiplier) - 3, color[1]);
}

void	init_minimap(t_data *data)
{
	int		color[2];
	int		multiplier;

	if (data->mini->mlx_img)
		data->prev_mini->mlx_img = data->mini->mlx_img;
	color[0] = encode_rgb(255, 255, 255);
	color[1] = encode_rgb(255, 0, 0);
	multiplier = 10;
	data->mini->mlx_img = mlx_new_image(data->mlx_ptr, \
	(data->file_cont->map_size.x + 2) * multiplier, \
	(data->file_cont->map_size.y + 2) * multiplier);
	data->mini->addr = mlx_get_data_addr(data->mini->mlx_img, \
		&data->mini->bits_per_pixel, &data->mini->line_length, \
			&data->mini->endian);
	draw_map(data, multiplier, color);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->mini->mlx_img, \
		0, 0);
	if (data->prev_mini->mlx_img)
	{
		mlx_destroy_image(data->mlx_ptr, data->prev_mini->mlx_img);
		data->prev_mini->mlx_img = 0;
	}
}
