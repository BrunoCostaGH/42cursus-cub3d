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

void	pix(t_img *img, int x, int y, int color)
{
	char		*dst;

	dst = img->addr + (y * img->line_length+ x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_vert_line(t_data *data, int x, int draw_start, int draw_end, int color)
{
	int	i;

	i = draw_start;
	while(i <= draw_end)
	{
		pix(data->img, x, i, color);
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

void	draw_ceiling(t_data *data)
{
	int x;
	int	red;
	int	green;
	int	blue;

	red = data->file_cont->colors[1][0];
	green = data->file_cont->colors[1][1];
	blue = data->file_cont->colors[1][2];
	x = 0;
	while (x <= data->window.x)
	{
		draw_vert_line(data, x, 0, data->window.y / 2, encode_rgb(red, green, blue));
		x++;
	}
}

void	draw_floor(t_data *data)
{
	int x;
	int	red;
	int	green;
	int	blue;

	red = data->file_cont->colors[0][0];
	green = data->file_cont->colors[0][1];
	blue = data->file_cont->colors[0][2];
	x = 0;
	while (x <= data->window.x)
	{
		draw_vert_line(data, x, data->window.y / 2, data->window.y, encode_rgb(red, green, blue));
		x++;
	}
}

int	handle_movement(int key, t_data *data)
{
	static t_data	*info;
	double	oldPlaneX;
	double	oldDirX;
	double	moveSpeed;
	double	rotSpeed;
	int		x;
	int 	y;

	if (!info)
		info = data;
	moveSpeed = 2;
	rotSpeed = 2;
	if (key == XK_w)
	{
		x = (int)info->ray.pos_x;
		y = (int)info->ray.pos_y;
		if (info->file_cont->map_arr[y][x])
		{
			info->ray.pos_x += info->ray.dir_x * moveSpeed;
			info->ray.pos_y += info->ray.dir_y * moveSpeed;
		}
	}
	if (key == XK_s)
	{
		x = (int) info->ray.pos_y;
		y = (int) (info->ray.pos_x - info->ray.dir_x * moveSpeed);
		if (info->file_cont->map_arr[y][x] == '0' || info->file_cont->map_arr[y][x] == 'N')
			info->ray.pos_x -= info->ray.dir_x * moveSpeed;
		x = (int) info->ray.pos_x;
		y = (int) (info->ray.pos_y - info->ray.dir_y * moveSpeed);
		if (info->file_cont->map_arr[y][x] == '0' || info->file_cont->map_arr[y][x] == 'N')
			info->ray.pos_y -= info->ray.dir_y * moveSpeed;
	}
	if (key == XK_d)
	{
		oldDirX = info->ray.dir_x;
		info->ray.dir_x = info->ray.dir_x * cos(-rotSpeed) - info->ray.dir_y * sin(-rotSpeed);
		info->ray.dir_y = oldDirX * sin(-rotSpeed) + info->ray.dir_y * cos(-rotSpeed);
		oldPlaneX = info->ray.plane_x;
		info->ray.plane_x = info->ray.plane_x * cos(-rotSpeed) - info->ray.plane_y * sin(-rotSpeed);
		info->ray.plane_y = oldPlaneX * sin(-rotSpeed) + info->ray.plane_y * cos(-rotSpeed);
	}
	if (key == XK_a)
	{
		oldDirX = info->ray.dir_x;
		info->ray.dir_x = info->ray.dir_x * cos(rotSpeed) - info->ray.dir_y * sin(rotSpeed);
		info->ray.dir_y = oldDirX * sin(rotSpeed) + info->ray.dir_y * cos(-rotSpeed);
		oldPlaneX = info->ray.plane_x;
		info->ray.plane_x = info->ray.plane_x * cos(rotSpeed) - info->ray.plane_y * sin(rotSpeed);
		info->ray.plane_y = oldPlaneX * sin(rotSpeed) + info->ray.plane_y * cos(rotSpeed);
	}
	return (0);
}

void	raycast(t_data *data)
{
	int 			x;
	static	int		i;

	if (i != 1)
	{
		data->ray.pos_x = data->player.init_pos.x + 0.5;
		data->ray.pos_y = data->player.init_pos.y + 0.5;
		get_dir_vector(data);
		data->ray.dir_x = data->player.init_dir_vec.x;
		data->ray.dir_y = data->player.init_dir_vec.y;
		data->ray.plane_x = 1;
		data->ray.plane_y = 0;
		//time = 0;
		//oldTime = 0;
		i = 1;
	}
	if (data->img->mlx_img)
	{
		mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
		data->img->mlx_img = 0;
	}
	data->img->mlx_img = mlx_new_image(data->mlx_ptr, data->window.x, data->window.y);
	data->img->addr = mlx_get_data_addr(data->img->mlx_img, &data->img->bits_per_pixel, &data->img->line_length, &data->img->endian);
	draw_floor(data);
	draw_ceiling(data);
	x = 0;
	while(x < data->window.x)
	{
		data->ray.color = encode_rgb(255, 0, 0);
		data->ray.mapX = (int) data->ray.pos_x;
		data->ray.mapY = (int) data->ray.pos_y;
		data->ray.hit = 0;
		data->ray.side = 0;
		data->ray.cameraX = 2 * x / data->window.x - 1;
		data->ray.ray_dir_x = data->ray.dir_x + data->ray.plane_x * data->ray.cameraX;
		data->ray.ray_dir_y = data->ray.dir_y + data->ray.plane_y * data->ray.cameraX;
		data->ray.delta_dist_X = fabs(1 / data->ray.ray_dir_x);
		data->ray.delta_dist_y = fabs(1 / data->ray.ray_dir_y);
		if (data->ray.ray_dir_x < 0)
		{
			data->ray.stepX = -1;
			data->ray.side_dist_X = (data->ray.pos_x - data->ray.mapX) * data->ray.delta_dist_X;
		}
		else
		{
			data->ray.stepX = 1;
			data->ray.side_dist_X = (data->ray.mapX + 1.0 - data->ray.pos_x) * data->ray.delta_dist_X;
		}
		if (data->ray.ray_dir_y < 0)
		{
			data->ray.stepY = -1;
			data->ray.side_dist_Y = (data->ray.pos_y - data->ray.mapY) * data->ray.delta_dist_y;
		}
		else
		{
			data->ray.stepY = 1;
			data->ray.side_dist_Y = (data->ray.mapY + 1.0 - data->ray.pos_y) * data->ray.delta_dist_y;
		}
		while (data->ray.hit == 0)
		{
			if (data->ray.side_dist_X < data->ray.side_dist_Y)
			{
				data->ray.side_dist_X += data->ray.delta_dist_X;
				data->ray.mapX += data->ray.stepX;
				data->ray.side = 0;
			}
			else
			{
				data->ray.side_dist_Y += data->ray.delta_dist_y;
				data->ray.mapY += data->ray.stepY;
				data->ray.side = 1;
			}
			if (data->file_cont->map_arr[data->ray.mapY][data->ray.mapX] != '0')
				data->ray.hit = 1;
		}
		if (data->ray.side == 0)
			data->ray.perp_wall_dist = data->ray.side_dist_X - data->ray.delta_dist_X;
		else
			data->ray.perp_wall_dist = data->ray.side_dist_Y - data->ray.delta_dist_y;
		data->ray.line_height = (int) (data->window.y / data->ray.perp_wall_dist);
		data->ray.draw_start = -data->ray.line_height / 2 + data->window.y / 2;
		if (data->ray.draw_start < 0)
			data->ray.draw_start = 0;
		data->ray.draw_end = data->ray.line_height / 2 + data->window.y / 2;
		if (data->ray.draw_end >= data->window.y)
			data->ray.draw_end = data->window.x - 1;
		if (data->ray.side == 0)
			data->ray.color = encode_rgb(255 / 2, 0, 0);
		draw_vert_line(data, x, data->ray.draw_start, data->ray.draw_end, data->ray.color);
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->mlx_img, 0, 0);
	data->ray.oldTime = data->ray.time;

}

void	start_game(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->window.x = 1280;
	data->window.y = 1024;
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window.x, data->window \
	.y, "cub3d");
	raycast(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_movement, data);
	mlx_loop(data->mlx_ptr);
}
