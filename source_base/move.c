/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:51:01 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/08 18:51:01 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_right(t_data *info, double move_speed)
{
	int	x;
	int	y;

	y = (int) info->ray.pos_y;
	x = (int)(info->ray.pos_x + info->ray.plane_x * move_speed);
	if (info->file_cont->map_arr[y][x] == '0')
		info->ray.pos_x += info->ray.plane_x * move_speed;
	x = (int) info->ray.pos_x;
	y = (int)(info->ray.pos_y + info->ray.plane_y * move_speed);
	if (info->file_cont->map_arr[y][x] == '0')
		info->ray.pos_y += info->ray.plane_y * move_speed;
}

void	move_left(t_data *info, double move_speed)
{
	int	x;
	int	y;

	y = (int) info->ray.pos_y;
	x = (int)(info->ray.pos_x - info->ray.plane_x * move_speed);
	if (info->file_cont->map_arr[y][x] == '0')
		info->ray.pos_x -= info->ray.plane_x * move_speed;
	x = (int) info->ray.pos_x;
	y = (int)(info->ray.pos_y - info->ray.plane_y * move_speed);
	if (info->file_cont->map_arr[y][x] == '0')
		info->ray.pos_y -= info->ray.plane_y * move_speed;
}

void	move_backwards(t_data *info, double move_speed)
{
	int	x;
	int	y;

	y = (int) info->ray.pos_y;
	x = (int)(info->ray.pos_x - info->ray.dir_x * move_speed);
	if (info->file_cont->map_arr[y][x] == '0')
		info->ray.pos_x -= info->ray.dir_x * move_speed;
	x = (int) info->ray.pos_x;
	y = (int)(info->ray.pos_y - info->ray.dir_y * move_speed);
	if (info->file_cont->map_arr[y][x] == '0')
		info->ray.pos_y -= info->ray.dir_y * move_speed;
}

void	move_forward(t_data *info, double move_speed)
{
	int	x;
	int	y;

	x = (int)(info->ray.pos_x + info->ray.dir_x * move_speed);
	y = (int)info->ray.pos_y;
	if (info->file_cont->map_arr[y][x] == '0')
		info->ray.pos_x += info->ray.dir_x * move_speed;
	x = (int) info->ray.pos_x;
	y = (int)(info->ray.pos_y + info->ray.dir_y * move_speed);
	if (info->file_cont->map_arr[y][x] == '0')
		info->ray.pos_y += info->ray.dir_y * move_speed;
}
