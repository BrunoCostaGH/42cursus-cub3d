/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:58:59 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/08 18:58:59 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_n(t_data *data)
{
	data->ray.dir_x = 0;
	data->ray.dir_y = -1;
	data->ray.plane_x = 1;
	data->ray.plane_y = 0;
}

void	set_s(t_data *data)
{
	data->ray.dir_x = 0;
	data->ray.dir_y = 1;
	data->ray.plane_x = -1;
	data->ray.plane_y = 0;
}

void	set_e(t_data *data)
{
	data->ray.dir_x = 1;
	data->ray.dir_y = 0;
	data->ray.plane_x = 0;
	data->ray.plane_y = 1;
}

void	set_w(t_data *data)
{
	data->ray.dir_x = -1;
	data->ray.dir_y = 0;
	data->ray.plane_x = 0;
	data->ray.plane_y = -1;
}
