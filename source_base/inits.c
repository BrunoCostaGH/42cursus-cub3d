/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:33:47 by tabreia-          #+#    #+#             */
/*   Updated: 2023/07/06 15:07:46 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_image(t_data *data, t_img *image)
{
	image->mlx_img = mlx_new_image(data->mlx_ptr, data->window.x, \
		data->window.y);
	image->addr = mlx_get_data_addr(image->mlx_img, \
		&image->bits_per_pixel, &image->line_length, \
			&image->endian);
	draw_floor(data);
	draw_ceiling(data);
}

void	init_moves(t_data *data)
{
	data->moves.right = false;
	data->moves.left = false;
	data->moves.forward = false;
	data->moves.back = false;
	data->moves.r_right = false;
	data->moves.r_left = false;
	data->moves.r_right_mouse = false;
	data->moves.r_left_mouse = false;
	data->moves.r_up = false;
	data->moves.r_down = false;
	data->moves.ctrl = false;
}

void	init_images(t_data *data)
{
	int	i;

	i = 0;
	data->img = malloc((sizeof(t_img)));
	data->img->mlx_img = 0;
	data->tex_img = ft_calloc(4 + 1, sizeof(t_img *));
	while (i < 4)
	{
		data->tex_img[i] = malloc(sizeof(t_img));
		data->tex_img[i]->mlx_img = 0;
		i++;
	}
}

void	init_file_cont(t_data *data)
{
	data->file_cont = malloc(sizeof(t_file));
	data->file_cont->map_arr = 0;
	data->file_cont->map_size.x = 0;
	data->file_cont->map_size.y = 0;
	data->file_cont->textures_path = ft_calloc(4 + 1, sizeof(char *));
	data->file_cont->colors = ft_calloc(3 + 1, sizeof(int *));
}

void	load_textures(t_data *data)
{
	int	i;
	int	size;

	i = 0;
	size = 64;
	while (i < 4)
	{
		data->tex_img[i]->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, \
			data->file_cont->textures_path[i], &size, &size);
		data->tex_img[i]->addr = \
			mlx_get_data_addr(data->tex_img[i]->mlx_img, \
				&data->tex_img[i]->bits_per_pixel, \
					&data->tex_img[i]->line_length, \
						&data->tex_img[i]->endian);
		i++;
	}
}
