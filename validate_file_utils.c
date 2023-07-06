/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:02:36 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/07/06 15:04:05 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_char(char c, bool for_player)
{
	if (for_player && c && (c == 'N' || c == 'S' || c == 'W' || c == 'E'))
		return (true);
	else if (for_player)
		return (false);
	if (c && (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || \
	c == 'E'))
		return (true);
	if (c && ft_isalnum(c))
	{
		write(2, "Error: `", 8);
		write(2, &c, 1);
		write(2, "': Invalid character\n", 21);
	}
	else
		write(2, "Error: Map not surrounded by walls\n", 35);
	return (false);
}

int	get_init_player_pos(t_data *data, char **map, int y)
{
	int	x;

	while (map[y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (is_valid_char(map[y][x], true) && (!data->player.init_dir && \
			!data->player.init_pos.x && !data->player.init_pos.y))
			{
				data->player.init_pos.x = x;
				data->player.init_pos.y = y;
				data->player.init_dir = map[y][x];
			}
			else if (is_valid_char(map[y][x], true) && \
			(data->player.init_dir != map[y][x] || data->player.init_pos.x != x \
			|| data->player.init_pos.y != y))
			{
				write(2, "Error: Detected multiple player spawn points\n", 45);
				return (1);
			}
		}
		y++;
	}
	return (0);
}
