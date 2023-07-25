/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:56:23 by tabreia-          #+#    #+#             */
/*   Updated: 2023/07/03 14:34:45 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

void	pix(t_data *data, int x, int y, int color)
{
	char		*pixel;
	t_img		*img;

	img = data->img;
	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
	//mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
}

void	draw_vert_line(t_data *data, int x, int draw_start, int draw_end, int color)
{
	int	i;

	i = draw_start;
	while(i <= draw_end)
	{
		pix(data, x, i, color);
		i++;
	}
}

void	get_dir_vector(t_data *data)
{
	if ('N' == data->player.init_dir)
	{
		data->player.init_dir_vec.x = 0;
		data->player.init_dir_vec.y = -1;
	}
	if ('S' == data->player.init_dir)
	{
		data->player.init_dir_vec.x = 0;
		data->player.init_dir_vec.y = 1;
	}
	if ('E' == data->player.init_dir)
	{
		data->player.init_dir_vec.x = 1;
		data->player.init_dir_vec.y = 0;
	}
	if ('W' == data->player.init_dir)
	{
		data->player.init_dir_vec.x = -1;
		data->player.init_dir_vec.y = 0;
	}
}

void	raycast(t_data *data)
{
	int 			x;
	int 			mapX;
	int 			mapY;
	int				stepX;
	int				stepY;
	int				side;
	int 			hit;
	int				line_height;
	int 			draw_start;
	int 			draw_end;
	int				color;
	static	int		i;
	static	double	pos_x;
	static	double	pos_y;
	static	double	dir_x;
	static	double	dir_y;
	static	double	plane_x;
	static	double	plane_y;
	//static	double	time;
	//static	double	oldTime;
	double			cameraX;
	double 			ray_dir_x;
	double 			ray_dir_y;
	double			side_dist_X;
	double			side_dist_Y;
	double			delta_dist_X;
	double			delta_dist_y;
	double			perp_wall_dist;

	if (i != 1)
	{
		pos_x = data->player.init_pos.x;
		pos_y = data->player.init_pos.y;
		get_dir_vector(data);
		dir_x = data->player.init_dir_vec.x;
		dir_y = data->player.init_dir_vec.y;
		plane_x = 1;
		plane_y = 0;
		//time = 0;
		//oldTime = 0;
		i = 1;
	}
	data->img->mlx_img = mlx_new_image(data->mlx_ptr, 640, 640);
	data->img->addr = mlx_get_data_addr(data->img->mlx_img, &data->img->bits_per_pixel, &data->img->line_length, &data->img->endian);
	x = 0;
	color = encode_rgb(255, 0, 0);
	while(x <= data->window.x)
	{
		mapX = (int) pos_x;
		mapY = (int) pos_y;
		hit = 0;
		cameraX = 2 * x / data->window.x - 1;
		ray_dir_x = dir_x + plane_x * cameraX;
		ray_dir_y = dir_y + plane_y * cameraX;
		delta_dist_X = fabs(1 / ray_dir_y);
		delta_dist_y = fabs(1 / ray_dir_y);
		if (ray_dir_x < 0)
		{
			stepX = -1;
			side_dist_X = (pos_x - mapX) * delta_dist_X;
		} else
		{
			stepX = -1;
			side_dist_X = (mapX + 1.0 - pos_x) * delta_dist_X;
		}
		if (ray_dir_y < 0)
		{
			stepY = -1;
			side_dist_Y = (pos_y - mapY) * delta_dist_y;
		}
		else
		{
			stepY = 1;
			side_dist_Y = (mapY + 1.0 - pos_y) * delta_dist_y;
		}
		while (hit == 0)
		{
			if (side_dist_X < side_dist_Y)
			{
				side_dist_X += delta_dist_X;
				mapX += stepX;
				side = 0;
			} else
			{
				side_dist_Y += delta_dist_y;
				mapY += stepY;
				side = 1;
			}
			if (data->file_cont->map_arr[mapY][mapX] != '0')
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = side_dist_X - delta_dist_X;
		else
			perp_wall_dist = side_dist_Y - delta_dist_y;
		line_height = (int) (data->window.x / perp_wall_dist);
		draw_start = -line_height / 2 + data->window.x / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + data->window.x / 2;
		if (draw_end >= data->window.x)
			draw_end = data->window.x - 1;
		draw_vert_line(data, x, draw_start, draw_end, color);
		x++;
	}
	//mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
}

void	start_game(t_data *data)
{
	data->mlx_ptr = mlx_init();

	data->window.x = 640;
	data->window.y = 480;
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window.x, data->window \
	.y, "cub3d");
	raycast(data);
	mlx_loop(data->mlx_ptr);
}
