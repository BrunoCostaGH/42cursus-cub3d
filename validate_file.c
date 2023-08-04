/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:23:44 by tabreia-          #+#    #+#             */
/*   Updated: 2023/07/06 15:07:56 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_valid_surrounding(char **map, char *point, int y)
{
	int	x;

	x = 0;
	while (&(map[y][x]) != point)
		x++;
	if (!map[y] || !map[y][x] || x == 0 || y == 0)
	{
		write(2, "Error: Map not surrounded by walls\n", 35);
		return (false);
	}
	return (is_valid_char(map[y - 1][x - 1], false) && \
			is_valid_char(map[y - 1][x], false) && \
			is_valid_char(map[y - 1][x + 1], false) && \
			is_valid_char(map[y][x - 1], false) && \
			is_valid_char(map[y][x + 1], false) && \
			is_valid_char(map[y + 1][x - 1], false) && \
			is_valid_char(map[y + 1][x], false) && \
			is_valid_char(map[y + 1][x + 1], false));
}

bool	valid_map(char **map)
{
	int		y;
	char	*current_floor;

	y = 0;
	current_floor = ft_strchr(map[y], '0');
	while (map[y])
	{
		if (current_floor)
		{
			if (check_valid_surrounding(map, current_floor, y) == false)
				return (false);
		}
		else
		{
			if (map[y + 1])
			{
				current_floor = ft_strchr(map[++y], '0');
				continue ;
			}
			break ;
		}
		current_floor = ft_strchr(current_floor + 1, '0');
	}
	return (true);
}

bool	valid_player(t_data *data, char **map)
{
	if (get_init_player_pos(data, map, 0))
		return (false);
	if (data->player.init_pos.x && data->player.init_pos.y && \
		data->player.init_dir && check_valid_surrounding(map, \
		&map[data->player.init_pos.y][data->player.init_pos.x], \
		data->player.init_pos.y))
		return (true);
	write(2, "Error: Missing or invalid player spawn point\n", 45);
	return (false);
}

bool	valid_cub_file(char *file_path, t_data *data)
{
	char	**map;

	if (read_file(file_path, data) == 0)
		return (false);
	map = check_for_data(data->file_cont->txt, data);
	if (valid_map(map) == false || valid_player(data, map) == false)
		return (false);
	free_char_arr(map);
	return (true);
}

bool	check_if_file_exists(char *file_path, int is_cub_file)
{
	int		fd;
	char	*file_ext;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		return (false);
	}
	close(fd);
	if (is_cub_file)
	{
		file_ext = ft_strchr(file_path, '.');
		if (!file_ext || ft_strncmp(file_ext, ".cub", ft_strlen(file_ext) + 1))
		{
			write(2, "Error: ", 7);
			write(2, file_ext, ft_strlen(file_ext));
			write(2, " is not a valid extension\n", 26);
			return (false);
		}
	}
	return (true);
}
