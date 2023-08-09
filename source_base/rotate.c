/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:56:26 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/08 18:56:26 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_right(t_data *info, double rot_speed)
{
	double	old_plane_x;
	double	old_dir_x;

	old_dir_x = info->ray.dir_x;
	info->ray.dir_x = info->ray.dir_x * cos(rot_speed) - \
			info->ray.dir_y * sin(rot_speed);
	info->ray.dir_y = old_dir_x * sin(rot_speed) + \
			info->ray.dir_y * cos(rot_speed);
	old_plane_x = info->ray.plane_x;
	info->ray.plane_x = info->ray.plane_x * cos(rot_speed) - \
			info->ray.plane_y * sin(rot_speed);
	info->ray.plane_y = old_plane_x * sin(rot_speed) + \
			info->ray.plane_y * cos(rot_speed);
}

void	rotate_left(t_data *info, double rot_speed)
{
	double	old_plane_x;
	double	old_dir_x;

	old_dir_x = info->ray.dir_x;
	info->ray.dir_x = info->ray.dir_x * cos(-rot_speed) - \
			info->ray.dir_y * sin(-rot_speed);
	info->ray.dir_y = old_dir_x * sin(-rot_speed) + \
			info->ray.dir_y * cos(-rot_speed);
	old_plane_x = info->ray.plane_x;
	info->ray.plane_x = info->ray.plane_x * cos(-rot_speed) - \
			info->ray.plane_y * sin(-rot_speed);
	info->ray.plane_y = old_plane_x * sin(-rot_speed) + \
			info->ray.plane_y * cos(-rot_speed);
}
