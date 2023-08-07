/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:56:23 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/07 16:44:09 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_file_cont(t_data *data)
{
	free_char_arr(data->file_cont->map_arr);
	free_char_arr(data->file_cont->txt);
	free_char_arr(data->file_cont->textures_path);
	free_int_arr(data->file_cont->colors);
	free(data->file_cont);
}

int	free_game(t_data *data)
{
	int i;

	if (data->img->mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->tex_img)
	{
		i = 0;
		while (data->tex_img[i])
		{
			mlx_destroy_image(data->mlx_ptr, data->tex_img[i]->mlx_img);
			free(data->tex_img[i++]);
		}
		free(data->tex_img);
	}
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_file_cont(data);
	free(data->img);
	free(data);
	exit(0);
}

int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

unsigned int	gix(t_img *img, int x, int y)
{
	return (*(unsigned int *)((img->addr + (y * img->line_length) + \
	x * (img->bits_per_pixel / 8))));
}

void	pix(t_img *img, int x, int y, int color)
{
	char		*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_vert_line(t_img *img, int x, int draw_start, int draw_end, int color)
{
	int	i;

	i = draw_start;
	while(i <= draw_end)
	{
		pix(img, x, i, color);
		i++;
	}
}

void	get_dir_vector(t_data *data)
{
	if ('N' == data->player.init_dir)
	{
		data->ray.dir_x = 0;
		data->ray.dir_y = -1;
		data->ray.plane_x = 1;
		data->ray.plane_y = 0;
	}
	if ('S' == data->player.init_dir)
	{
		data->ray.dir_x = 0;
		data->ray.dir_y = 1;
		data->ray.plane_x = -1;
		data->ray.plane_y = 0;
	}
	if ('E' == data->player.init_dir)
	{
		data->ray.dir_x = 1;
		data->ray.dir_y = 0;
		data->ray.plane_x = 0;
		data->ray.plane_y = 1;
	}
	if ('W' == data->player.init_dir)
	{
		data->ray.dir_x = -1;
		data->ray.dir_y = 0;
		data->ray.plane_x = 0;
		data->ray.plane_y = -1;
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
		draw_vert_line(data->img, x, 0, data->window.y / 2, encode_rgb(red, green, blue));
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
		draw_vert_line(data->img, x, data->window.y / 2, data->window.y, encode_rgb(red, green, blue));
		x++;
	}
}

int	handle_movement(t_data *data)
{
	static t_data	*info;
	double			oldPlaneX;
	double			oldDirX;
	double			moveSpeed;
	double			rotSpeed;
	int				x;
	int 			y;

	info = (t_data *)data;
	moveSpeed = 0.1;
	rotSpeed = 0.1;
	if (data->moves.forward == true)
	{
		x = (int)(info->ray.pos_x + info->ray.dir_x * moveSpeed);
		y = (int)info->ray.pos_y;
		if (info->file_cont->map_arr[y][x] == '0')
			info->ray.pos_x += info->ray.dir_x * moveSpeed;
		x = (int) info->ray.pos_x;
		y = (int) (info->ray.pos_y + info->ray.dir_y * moveSpeed);
		if (info->file_cont->map_arr[y][x] == '0')
			info->ray.pos_y += info->ray.dir_y * moveSpeed;
	}
	if (data->moves.back == true)
	{
		y = (int) info->ray.pos_y;
		x = (int) (info->ray.pos_x - info->ray.dir_x * moveSpeed);
		if (info->file_cont->map_arr[y][x] == '0')
			info->ray.pos_x -= info->ray.dir_x * moveSpeed;
		x = (int) info->ray.pos_x;
		y = (int) (info->ray.pos_y - info->ray.dir_y * moveSpeed);
		if (info->file_cont->map_arr[y][x] == '0')
			info->ray.pos_y -= info->ray.dir_y * moveSpeed;
	}
	if (data->moves.left == true)
	{
		y = (int) info->ray.pos_y;
		x = (int) (info->ray.pos_x - info->ray.plane_x * moveSpeed);
		if (info->file_cont->map_arr[y][x] == '0')
			info->ray.pos_x -= info->ray.plane_x * moveSpeed;
		x = (int) info->ray.pos_x;
		y = (int) (info->ray.pos_y - info->ray.plane_y * moveSpeed);
		if (info->file_cont->map_arr[y][x] == '0')
			info->ray.pos_y -= info->ray.plane_y * moveSpeed;
	}
	if (data->moves.right == true)
	{
		y = (int) info->ray.pos_y;
		x = (int) (info->ray.pos_x + info->ray.plane_x * moveSpeed);
		if (info->file_cont->map_arr[y][x] == '0')
			info->ray.pos_x += info->ray.plane_x * moveSpeed;
		x = (int) info->ray.pos_x;
		y = (int) (info->ray.pos_y + info->ray.plane_y * moveSpeed);
		if (info->file_cont->map_arr[y][x] == '0')
			info->ray.pos_y += info->ray.plane_y * moveSpeed;
	}
	if (data->moves.r_left == true)
	{
		oldDirX = info->ray.dir_x;
		info->ray.dir_x = info->ray.dir_x * cos(-rotSpeed) - info->ray.dir_y * sin(-rotSpeed);
		info->ray.dir_y = oldDirX * sin(-rotSpeed) + info->ray.dir_y * cos(-rotSpeed);
		oldPlaneX = info->ray.plane_x;
		info->ray.plane_x = info->ray.plane_x * cos(-rotSpeed) - info->ray.plane_y * sin(-rotSpeed);
		info->ray.plane_y = oldPlaneX * sin(-rotSpeed) + info->ray.plane_y * cos(-rotSpeed);
	}
	if (data->moves.r_right == true)
	{
		oldDirX = info->ray.dir_x;
		info->ray.dir_x = info->ray.dir_x * cos(rotSpeed) - info->ray.dir_y * sin(rotSpeed);
		info->ray.dir_y = oldDirX * sin(rotSpeed) + info->ray.dir_y * cos(rotSpeed);
		oldPlaneX = info->ray.plane_x;
		info->ray.plane_x = info->ray.plane_x * cos(rotSpeed) - info->ray.plane_y * sin(rotSpeed);
		info->ray.plane_y = oldPlaneX * sin(rotSpeed) + info->ray.plane_y * cos(rotSpeed);
	}
	return (0);
}

void	apply_texture(t_data *data, int x, int id)
{
	double			wallX;
	double			step;
	double			texPos;
	int				texX;
	int				texY;
	int				y;
	unsigned int	color;

	if (data->ray.side == 0)
	{
		wallX = data->ray.pos_y + data->ray.perp_wall_dist * data->ray.ray_dir_y;
		wallX -= data->ray.mapY;
	}
	else
	{
		wallX = data->ray.pos_x + data->ray.perp_wall_dist * data->ray.ray_dir_x;
		wallX -= data->ray.mapX;
	}
	texX = (int) (wallX * (double)64);
	texX = 64 - texX - 1;
	step = 1.0 * 64 / data->ray.line_height;
	texPos = (data->ray.draw_start - data->window.y / 2 + data->ray.line_height / 2) * step;
	y = data->ray.draw_start;
	while (y < data->ray.draw_end && y < data->window.y)
	{
		texY = ((int) texPos & (64 - 1));
		texPos += step;
		if (x >= 0)
		{
			color = gix(data->tex_img[id], texX, texY);
			pix(data->img, x, y, color);
		}
		y++;
	}
}

/*
 * id 0 is N texture
 * id 1 is S texture
 * id 2 is W texture
 * id 3 is E texture
 */

void	texture_picker(t_data *data)
{
	if (data->ray.ray_dir_x < 0)
	{
		if (data->ray.side == 0)
		{
			data->id = 3;
			return ;
		}
		if (data->ray.ray_dir_y < 0)
		{
			data->id = 1;
			return ;
		}
		else
		{
			data->id = 0;
			return ;
		}
	}
	else
	{
		if (data->ray.side == 0)
		{
			data->id = 2;
			return ;
		}
		if (data->ray.ray_dir_y < 0)
		{
			data->id = 1;
			return ;
		}
		else
		{
			data->id = 0;
			return ;
		}
	}
}
/*
void	texture_picker(t_data *data)
{
	//Left side
	if (data->ray.ray_dir_x < 0 && data->ray.ray_dir_y < 0 && data->ray.side == 1)
		data->id = 0;
	else if (data->ray.ray_dir_x < 0 && data->ray.ray_dir_y > 0 && data->ray.side == 1)
		data->id = 1;
	else if (data->ray.ray_dir_x < 0 && data->ray.side == 0)
	{
		data->id = 2;
		return ;
	}
	//Right side
	if (data->ray.ray_dir_x > 0 && data->ray.ray_dir_y > 0 && data->ray.side == 1)
		data->id = 0;
	else if (data->ray.ray_dir_x > 0 && data->ray.ray_dir_y < 0 && data->ray.side == 1)
		data->id = 1;
	else if (data->ray.ray_dir_x > 0 && data->ray.side == 0)
	{
		data->id = 3;
		return ;
	}
	//North side
	if (data->ray.ray_dir_y < 0 && data->ray.ray_dir_x > 0 && data->ray.side == 0)
		data->id = 2;
	else if (data->ray.ray_dir_y < 0 && data->ray.ray_dir_x < 0 && data->ray.side == 0)
		data->id = 3;
	else if (data->ray.ray_dir_y < 0 && data->ray.side == 1)
	{
		data->id = 1;
		return ;
	}
	//South side
	if (data->ray.ray_dir_y > 0 && data->ray.ray_dir_x > 0 && data->ray.side == 0)
		data->id = 2;
	else if (data->ray.ray_dir_y > 0 && data->ray.ray_dir_x < 0 && data->ray.side == 0)
		data->id = 3;
	else if (data->ray.ray_dir_y > 0 && data->ray.side == 1)
	{
		data->id = 0;
		return ;
	}
}*/

int	raycast(void *v_data)
{
	int 			x;
	static	int		i;
	t_data *data;

	data = (t_data *)v_data;
	if (i != 1)
	{
		data->ray.pos_x = data->player.init_pos.x + 0.5;
		data->ray.pos_y = data->player.init_pos.y + 0.5;
		get_dir_vector(data);
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
		texture_picker(data);
		apply_texture(data, x, data->id);
		//draw_vert_line(data, x, data->ray.draw_start, data->ray.draw_end, data->ray.color);
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->mlx_img, 0, 0);
	handle_movement(data);
	init_minimap(data);
	return (0);
}

int handle_keyRelease(int key, t_data *data)
{
	if (key == XK_w)
		data->moves.forward = false;
	if (key == XK_s)
		data->moves.back = false;
	if (key == XK_d)
		data->moves.right = false;
	if (key == XK_a)
		data->moves.left = false;
	if (key == XK_Left)
		data->moves.r_left = false;
	if (key == XK_Right)
		data->moves.r_right = false;
	return (0);
}


int	handle_keypress(int key, t_data *data)
{
	if (key == XK_w)
		data->moves.forward = true;
	if (key == XK_s)
		data->moves.back = true;
	if (key == XK_d)
		data->moves.right = true;
	if (key == XK_a)
		data->moves.left = true;
	if (key == XK_Left)
		data->moves.r_left = true;
	if (key == XK_Right)
		data->moves.r_right = true;
	if (key == XK_Escape)
		free_game(data);
	return (0);
}

void	load_textures(t_data *data)
{
	int i;
	int size;
	//int k;

	i = 0;
	size = 64;
	while (i < 4)
	{
		//k = 0;
		//data->tex_img[i]->mlx_img = mlx_new_image(data->mlx_ptr, size, size);
		data->tex_img[i]->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, data->file_cont->textures_path[i], &size, &size);
		data->tex_img[i]->addr = mlx_get_data_addr(data->tex_img[i]->mlx_img, &data->tex_img[i]->bits_per_pixel, &data->tex_img[i]->line_length, &data->tex_img[i]->endian);
		//mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tex_img[i]->mlx_img, 0, size * i);
		/*while (k <= 64)
		{
			draw_vert_line(data->tex_img[i],k, 0, 64, encode_rgb(255, 0, 0));
			k++;
		}*/
		i++;
	}
}

void	start_game(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window.x, data->window \
	.y, "cub3d");
	load_textures(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &handle_keyRelease, data);
	mlx_hook(data->win_ptr, 17, 1L << 17, free_game, data);
	mlx_loop_hook(data->mlx_ptr, &raycast, data);
	mlx_loop(data->mlx_ptr);
}
