/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:49:34 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/09 14:58:38 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	apply_texture_2(t_data *data, int x, int id, t_point *tex)
{
	double			tex_pos;
	double			step;
	int				y;

	step = 1.0 * 64 / data->ray.line_height;
	tex_pos = (data->ray.draw_start - data->draw_mid_point + \
		data->ray.line_height / 2) * step;
	y = data->ray.draw_start;
	while (y < data->ray.draw_end && y < data->window.y)
	{
		tex->y = ((int) tex_pos & (64 - 1));
		tex_pos += step;
		if (x >= 0 && y >= 0 && tex->x >= 0 && tex->y >= 0)
		{
			data->ray.color = gix(data->tex_img[id], tex->x, tex->y);
			pix(data->img, x, y, data->ray.color);
		}
		y++;
	}
}

void	apply_texture(t_data *data, int x, int id)
{
	double			wall_x;
	t_point			tex;

	if (data->ray.side == 0)
	{
		wall_x = data->ray.pos_y + data->ray.perp_wall_dist * \
			data->ray.ray_dir_y;
		wall_x -= data->ray.map_y;
	}
	else
	{
		wall_x = data->ray.pos_x + data->ray.perp_wall_dist * \
			data->ray.ray_dir_x;
		wall_x -= data->ray.map_x;
	}
	tex.x = (int)(wall_x * (double)64);
	tex.x = 64 - tex.x - 1;
	apply_texture_2(data, x, id, &tex);
}

/*
 * id 0 is N texture
 * id 1 is S texture
 * id 2 is W texture
 * id 3 is E texture
 */
void	texture_picker(t_data *data)
{
	if (data->ray.ray_dir_x < 0 && data->ray.side == 0)
	{
		data->id = 3;
		return ;
	}
	else if (data->ray.side == 0)
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
