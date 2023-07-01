/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:56:23 by tabreia-          #+#    #+#             */
/*   Updated: 2023/06/17 17:56:23 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_player_char(char c, t_data *data)
{
	if (c == 'N')
	{
		data->player.init_dir = 'N';
		return (true);
	}
	if (c == 'S')
	{
		data->player.init_dir = 'S';
		return (true);
	}
	if (c == 'E')
	{
		data->player.init_dir = 'E';
		return (true);
	}
	if (c == 'W')
	{
		data->player.init_dir = 'W';
		return (true);
	}
	return (false);
}

void	get_init_player_pos(char **map, t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player_char(map[y][x], data))
			{
				data->player.init_pos.x = x;
				data->player.init_pos.y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	start_game(t_data *data)
{
	get_init_player_pos(data->file_cont->map_arr, data);
	data->mlx_ptr = mlx_init();
	data->window.x = 640;
	data->window.y = 640;
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window.x, data->window \
	.y, "cub3d");
	mlx_loop(data->mlx_ptr);
}
