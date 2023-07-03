/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia@student.42porto.pt>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:23:44 by tabreia-          #+#    #+#             */
/*   Updated: 2023/07/03 15:07:41 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_char(t_data *data, char c, int y, int x)
{
	if (c && (c == '0' || c == '1'))
		return (true);
	if (c && (c == 'N' || c == 'S' || c == 'W' || c == 'E'))
	{
		if (!data->player.init_dir && !data->player.init_pos.x && \
		!data->player.init_pos.y)
		{
			data->player.init_pos.x = x;
			data->player.init_pos.y = y;
			data->player.init_dir = c;
		}
		else if (data->player.init_dir != c || data->player.init_pos.x != x || \
		data->player.init_pos.y != y)
		{
			write(2, "Error: Detected multiple player spawn points\n", 45);
			return (false);
		}
		return (true);
	}
	write(2, "Error: Map not surrounded by walls\n", 35);
	return (false);
}

bool	check_valid_surrounding(t_data *data, char **map, char *point, int y)
{
	int	x;

	x = 0;
	while (&(map[y][x]) != point)
		x++;
	if (!map[y][x] || x == 0 || y == 0)
	{
		write(2, "Error: Map not surrounded by walls\n", 35);
		return (false);
	}
	return (is_valid_char(data, map[y - 1][x - 1], y - 1, x - 1) && \
			is_valid_char(data, map[y - 1][x], y - 1, x) && \
			is_valid_char(data, map[y - 1][x + 1], y - 1, x + 1) && \
			is_valid_char(data, map[y][x - 1], y, x - 1) && \
			is_valid_char(data, map[y][x + 1], y, x + 1) && \
			is_valid_char(data, map[y + 1][x - 1], y + 1, x - 1) && \
			is_valid_char(data, map[y + 1][x], y + 1, x) && \
			is_valid_char(data, map[y + 1][x + 1], y + 1, x + 1));
}

bool	valid_map(t_data *data, char **map)
{
	int		i;
	char	*current_floor;

	i = 0;
	current_floor = ft_strchr(map[i], '0');
	while (map[i])
	{
		if (current_floor)
		{
			if (check_valid_surrounding(data, map, current_floor, i) == false)
				return (false);
		}
		else
		{
			if (map[i + 1])
			{
				current_floor = ft_strchr(map[++i], '0');
				continue ;
			}
			break ;
		}
		current_floor = ft_strchr(current_floor + 1, '0');
	}
	return (true);
}

bool	valid_cub_file(char *file_path, t_data *data)
{
	char	**map_val;

	if (read_file(file_path, data) == 0)
		return (false);
	map_val = check_for_data(data->file_cont->txt, data);
	if (valid_map(data, map_val) == false)
		return (false);
	if (!data->player.init_pos.x || !data->player.init_pos.y || \
	!data->player.init_dir)
	{
		write(2, "Error: Missing or invalid player spawn point\n", 45);
		return (false);
	}
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
