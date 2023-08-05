/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 21:11:42 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/07/06 21:11:59 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vision_cone_mir(t_data *data)
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;
	double	x;
	double	y;
	double 	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		dx;
	int		dy;
	int		p;
	int		end;

	plane_y = data->ray.plane_y * 10;
	plane_x = data->ray.plane_x * 10;
	dir_x = data->ray.dir_x * 10;
	dir_y = data->ray.dir_y * 10;
	x1 = (data->ray.pos_x * 10);
	y1 = (data->ray.pos_y * 10);
	x2 = (data->ray.pos_x * 10) + (dir_x - plane_x);
	y2 = (data->ray.pos_y * 10) + (dir_y - plane_y);
	dx = fabs(x1 - x2);
	dy = fabs(y1 - y2);
	p = 2 * dy - dx;
	if(x1 > x2)
	{
		x = x2;
		y = y2;
		end = x1;
	}
	else
	{
		x = x1;
		y = y1;
		end = x2;
	}
	pix(data->mini, x, y, encode_rgb(0, 255, 0));
	while (x < end)
	{
		if (p < 0)
			p += 2 * dy;
		else
		{
			y++;
			p += 2 * (dy - dx);
		}
		pix(data->mini, x, y, encode_rgb(0, 255, 0));
		x++;
	}
}

void	draw_vision_cone(t_data *data)
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;
	double	x;
	double	y;
	double 	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		dx;
	int		dy;
	int		p;
	int		end;

	plane_y = data->ray.plane_y * 10;
	plane_x = data->ray.plane_x * 10;
	dir_x = data->ray.dir_x * 10;
	dir_y = data->ray.dir_y * 10;
	x1 = (data->ray.pos_x * 10);
	y1 = (data->ray.pos_y * 10);
	x2 = (data->ray.pos_x * 10) + (dir_x + plane_x);
	y2 = (data->ray.pos_y * 10) + (dir_y + plane_y);
	dx = fabs(x1 - x2);
	dy = fabs(y1 - y2);
	p = 2 * dy - dx;
	if(x1 > x2)
	{
		x = x2;
		y = y2;
		end = x1;
	}
	else
	{
		x = x1;
		y = y1;
		end = x2;
	}
	pix(data->mini, x, y, encode_rgb(0, 255, 0));
	while (x < end)
	{
		if (p < 0)
			p += 2 * dy;
		else
		{
			y++;
			p += 2 * (dy - dx);
		}
		pix(data->mini, x, y, encode_rgb(0, 255, 0));
		x++;
	}
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


	if (data->mini->mlx_img)
	{
		mlx_destroy_image(data->mlx_ptr, data->mini->mlx_img);
		data->mini->mlx_img = 0;
	}
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
	draw_square_player(data, ((data->ray.pos_y) * multiplier) - 3, ((data->ray.pos_x ) * multiplier)- 3, color[1]);
	draw_vision_cone(data);
	draw_vision_cone_mir(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->mini->mlx_img, 0, 0);
}
