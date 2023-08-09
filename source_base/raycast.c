/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:14:56 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/09 15:39:23 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	calc_step(t_data *data)
{
	if (data->ray.ray_dir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->ray.pos_x - data->ray.map_x) * \
				data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - data->ray.pos_x) * \
				data->ray.delta_dist_x;
	}
	if (data->ray.ray_dir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->ray.pos_y - data->ray.map_y) * \
				data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - data->ray.pos_y) * \
				data->ray.delta_dist_y;
	}
}

static void	init_calc(t_data *data, int x)
{
	data->ray.color = encode_rgb(255, 0, 0);
	data->ray.map_x = (int) data->ray.pos_x;
	data->ray.map_y = (int) data->ray.pos_y;
	data->ray.hit = 0;
	data->ray.side = 0;
	data->ray.camera_x = 2 * x / data->window.x - 1;
	data->ray.ray_dir_x = data->ray.dir_x + data->ray.plane_x * \
			data->ray.camera_x;
	data->ray.ray_dir_y = data->ray.dir_y + data->ray.plane_y * \
			data->ray.camera_x;
	data->ray.delta_dist_x = fabs(1 / data->ray.ray_dir_x);
	data->ray.delta_dist_y = fabs(1 / data->ray.ray_dir_y);
}

static void	calculate_drawpoints(t_data *data)
{
	if (data->ray.side == 0)
		data->ray.perp_wall_dist = data->ray.side_dist_x - \
				data->ray.delta_dist_x;
	else
		data->ray.perp_wall_dist = data->ray.side_dist_y - \
				data->ray.delta_dist_y;
	data->ray.line_height = (int)(data->window.y / \
			data->ray.perp_wall_dist);
	data->ray.draw_start = -data->ray.line_height / 2 + data->window.y / 2;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	data->ray.draw_end = data->ray.line_height / 2 + data->window.y / 2;
	if (data->ray.draw_end >= data->window.y)
		data->ray.draw_end = data->window.x - 1;
}

static void	dda_algo(t_data *data)
{
	while (data->ray.hit == 0)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		if (data->file_cont->map_arr[data->ray.map_y][data->ray.map_x] != '0')
			data->ray.hit = 1;
	}
}

int	raycast(t_data *data)
{
	int	x;

	if (data->img->mlx_img)
	{
		mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
		data->img->mlx_img = 0;
	}
	init_image(data, data->img);
	draw_floor(data);
	draw_ceiling(data);
	x = 0;
	while (x++ < data->window.x)
	{
		init_calc(data, x);
		calc_step(data);
		dda_algo(data);
		calculate_drawpoints(data);
		texture_picker(data);
		apply_texture(data, x, data->id);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
		data->img->mlx_img, 0, 0);
	handle_movement(data);
	return (0);
}
