/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:48:53 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/10 18:51:52 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_ceiling(t_data *data)
{
	int	x;
	int	red;
	int	green;
	int	blue;

	red = data->file_cont->colors[1][0];
	green = data->file_cont->colors[1][1];
	blue = data->file_cont->colors[1][2];
	x = 0;
	data->ray.color = encode_rgb(red, green, blue);
	while (x <= data->window.x)
	{
		draw_vert_line(data->img, (t_point){x, 0}, \
		(t_point){x, data->draw_mid_point}, data->ray.color);
		x++;
	}
}

void	draw_floor(t_data *data)
{
	int	x;
	int	red;
	int	green;
	int	blue;

	red = data->file_cont->colors[0][0];
	green = data->file_cont->colors[0][1];
	blue = data->file_cont->colors[0][2];
	x = 0;
	data->ray.color = encode_rgb(red, green, blue);
	while (x <= data->window.x)
	{
		draw_vert_line(data->img, (t_point){x, data->draw_mid_point}, \
		(t_point){x, data->window.y}, data->ray.color);
		x++;
	}
}
