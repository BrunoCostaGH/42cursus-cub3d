/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:47:43 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/08 18:47:43 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	draw_vert_line(t_data *data, int x, int draw_start, int draw_end)
{
	int	i;

	i = draw_start;
	while (i <= draw_end && x >= 0 && i >= 0)
	{
		pix(data->img, x, i, data->ray.color);
		i++;
	}
}
