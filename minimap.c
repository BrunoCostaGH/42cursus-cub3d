/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 21:11:42 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/08/07 18:05:08 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_r(t_data *data, t_point p0, t_point p1, t_point cur)
{
	double	s;
	double	step;

	s = (float)(p1.y - p0.y) / (float)(p1.x - p0.x);
	step = p1.y - s * p1.x;
	cur = p0;
	if (p0.x <= p1.x)
	{
		while (cur.x <= p1.x)
		{
			if (cur.x > 0 && round(s * cur.x + step) > 0)
				pix(data->mini, cur.x, round(s * cur.x + step), encode_rgb(0, 255, 0));
			cur.x++;
		}
	}
	else if (p0.x > p1.x)
	{
		while (cur.x >= p1.x)
		{
			if (cur.x > 0 && round(s * cur.x + step) > 0)
				pix(data->mini, cur.x, round(s * cur.x + step), encode_rgb(0, 255, 0));
			cur.x--;
		}
	}
}

// Draw reverse slope
void	draw_line_rr(t_data *data, t_point p0, t_point p1, t_point cur)
{
	double	s;
	double	step;

	s = (float)(p1.y - p0.y) / (float)(p1.x - p0.x);
	step = p1.y - s * p1.x;
	cur = p0;
	if (p0.y <= p1.y)
	{
		while (cur.y <= p1.y)
		{
			if (cur.y > 0 && round((cur.y - step) / s) > 0)
				pix(data->mini, round((cur.y - step) / s), cur.y, encode_rgb(0, 255, 0));
			cur.y++;
		}
	}
	else if (p0.y > p1.y)
	{
		while (cur.y >= p1.y)
		{
			if (cur.y > 0 && round((cur.y - step) / s) > 0)
				pix(data->mini, round((cur.y - step) / s), cur.y, encode_rgb(0, 255, 0));
			cur.y--;
		}
	}
}

void	draw_line(t_data *data, t_point p0, t_point p1)
{
	double	s;
	t_point	cur;

	s = (float)(p1.y - p0.y) / (float)(p1.x - p0.x);
	cur.x = 0;
	cur.y = 0;
	if (s <= 1 && s >= -1)
		draw_line_r(data, p0, p1, cur);
	else
		draw_line_rr(data, p0, p1, cur);
}

void	draw_square_player(t_data *data, int y, int x, int color)
{
	int i;

	i = 0;
	while (i++ < 6)
		draw_vert_line(data->mini, x + i, y, y + 6, color);
}

void	draw_square(t_data *data, int y, int x, int color)
{
	int i;

	i = 0;
	while (i++ < 10)
		draw_vert_line(data->mini, x + i, y, y + 10, color);
}

void	init_minimap(t_data *data)
{
	int		x;
	int		y;
	int		color[2];
	int		multiplier;
	int		size;
	t_point player;
	t_point hp;

	if (data->mini->mlx_img)
		data->prev_mini->mlx_img = data->mini->mlx_img;
	size = 10;
	color[0] = encode_rgb(255, 255, 255);
	color[1] = encode_rgb(255, 0, 0);
	multiplier = 10;
	data->mini->mlx_img = mlx_new_image(data->mlx_ptr, \
	(data->file_cont->map_size.x + 2) * multiplier, \
	(data->file_cont->map_size.y + 2) * multiplier);
	data->mini->addr = mlx_get_data_addr(data->mini->mlx_img, &data->mini->bits_per_pixel, \
	&data->mini->line_length, &data->mini->endian);
	y = 0;
	player.x = data->ray.pos_x * multiplier;
	player.y = data->ray.pos_y * multiplier;
	hp.x = (data->min_fov_hp.x * multiplier) + (data->min_fov_dec * multiplier);
	hp.y = (data->min_fov_hp.y * multiplier) + (data->min_fov_dec * multiplier);
	draw_line(data, player, hp);
	hp.x = (data->max_fov_hp.x * multiplier) + (data->max_fov_dec * multiplier);
	hp.y = (data->max_fov_hp.y * multiplier) + (data->max_fov_dec * multiplier);
	draw_line(data, player, hp);
	while (data->file_cont->map_arr[y])
	{
		x = 0;
		while (data->file_cont->map_arr[y][x])
		{
			if (data->file_cont->map_arr[y][x] == '1')
				draw_square(data, y * size, x * size, color[0]);
			x++;
		}
		y++;
	}
	draw_square_player(data, ((data->ray.pos_y) * multiplier) - 3, ((data->ray.pos_x ) * multiplier) - 3, color[1]);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->mini->mlx_img, 0, 0);
	if (data->prev_mini->mlx_img)
	{
		mlx_destroy_image(data->mlx_ptr, data->prev_mini->mlx_img);
		data->prev_mini->mlx_img = 0;
	}
}
