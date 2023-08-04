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

void	init_minimap(t_data *data)
{
	int		index[2];
	int		color[2];
	int		multiplier;
	t_img	*minimap;

	color[0] = encode_rgb(255, 255, 255);
	color[1] = encode_rgb(255, 0, 0);
	multiplier = 10;
	minimap = malloc(sizeof(t_img));
	minimap->mlx_img = mlx_new_image(data->mlx_ptr, \
	(data->file_cont->map_size.x + 2) * multiplier, \
	(data->file_cont->map_size.y + 2) * multiplier);
	minimap->addr = mlx_get_data_addr(minimap->mlx_img, &minimap->bits_per_pixel, \
	&minimap->line_length, &minimap->endian);
	index[0] = 0;
	while (data->file_cont->map_arr[index[0]])
	{
		index[1] = 0;
		while (data->file_cont->map_arr[index[0]][index[1]])
		{
			if (data->file_cont->map_arr[index[0]][index[1]] == '1')
				pix(minimap, (index[1] + 1) * multiplier, (index[0] + 1) * multiplier, color[0]);
			index[1]++;
		}
		index[0]++;
	}
	pix(minimap, (data->ray.pos_x + 1) * multiplier, (data->ray.pos_y + 1) * multiplier, color[1]);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, minimap->mlx_img, 0, 0);
}
