/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:47:43 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/10 16:16:21 by bsilva-c         ###   ########.fr       */
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

void	draw_vert_line(t_img *img, t_point draw_start, t_point draw_end, \
						int color)
{
	while (draw_start.x >= 0 && draw_start.y >= 0 && draw_start.y <= draw_end.y)
	{
		pix(img, draw_start.x, draw_start.y, color);
		draw_start.y++;
	}
}
