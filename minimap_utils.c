/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:43:13 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/08/10 17:50:09 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static void	draw_line_r(t_data *data, t_point p0, t_point p1)
{
	double	s;
	double	step;

	s = (float)(p1.y - p0.y) / (float)(p1.x - p0.x);
	step = p1.y - s * p1.x;
	if (p0.x <= p1.x)
	{
		while (p0.x <= p1.x)
		{
			if (p0.x >= 0 && round(s * p0.x + step) >= 0)
				pix(data->mini, p0.x, round(s * p0.x + step), \
				encode_rgb(0, 255, 0));
			p0.x++;
		}
	}
	else if (p0.x > p1.x)
	{
		while (p0.x >= p1.x)
		{
			if (p0.x >= 0 && round(s * p0.x + step) >= 0)
				pix(data->mini, p0.x, round(s * p0.x + step), \
				encode_rgb(0, 255, 0));
			p0.x--;
		}
	}
}

// Draw reverse slope
static void	draw_line_rr(t_data *data, t_point p0, t_point p1)
{
	double	s;
	double	step;

	s = (float)(p1.y - p0.y) / (float)(p1.x - p0.x);
	step = p1.y - s * p1.x;
	if (p0.y <= p1.y)
	{
		while (p0.y <= p1.y)
		{
			if (p0.y >= 0 && round((p0.y - step) / s) >= 0)
				pix(data->mini, round((p0.y - step) / s), p0.y, \
				encode_rgb(0, 255, 0));
			p0.y++;
		}
	}
	else if (p0.y > p1.y)
	{
		while (p0.y >= p1.y)
		{
			if (p0.y >= 0 && round((p0.y - step) / s) >= 0)
				pix(data->mini, round((p0.y - step) / s), p0.y, \
				encode_rgb(0, 255, 0));
			p0.y--;
		}
	}
}

void	draw_line(t_data *data, t_point p0, t_point p1)
{
	double	s;

	s = (float)(p1.y - p0.y) / (float)(p1.x - p0.x);
	if (s <= 1 && s >= -1)
		draw_line_r(data, p0, p1);
	else
		draw_line_rr(data, p0, p1);
}

void	draw_square_player(t_data *data, int y, int x, int color)
{
	int	i;

	i = 0;
	while (i++ < 6)
		draw_vert_line(data->mini, (t_point){x + i, y}, \
		(t_point){x + i, y + 6}, color);
}

void	draw_square(t_data *data, int y, int x, int color)
{
	int	i;

	i = 0;
	while (i++ < 10)
		draw_vert_line(data->mini, (t_point){x + i, y}, \
		(t_point){x + i, y + 10}, color);
}
