/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia@student.42porto.pt>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:23:44 by tabreia-          #+#    #+#             */
/*   Updated: 2023/07/01 19:53:08 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_max_yx(char **map, t_data *data)
{
	int	y;
	int	x;
	int	y_ret;
	int	x_ret;

	y = 0;
	while (map[y])
		y++;
	y_ret = y - 1;
	y = 0;
	x_ret = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (x > x_ret)
				x_ret = x;
			x++;
		}
		y++;
	}
	data->max.x = x_ret;
	data->max.y = y_ret;
}

void	get_start_point(char **map, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y <= data->max.y)
	{
		x = 0;
		while (x <= data->max.x && !data->flood_point.x)
		{
			if (map[y][x] == '1')
			{
				data->flood_point.x = x;
				data->flood_point.y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

bool	is_valid_char(char c)
{
	if (!c)
		return (false);
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

bool	check_valid_surrounding(char **map, const char *tile, int y)
{
	int	x;

	x = 0;
	while (map[y][x] != *tile)
		x++;
	if (!map[y][x] || x == 0 || y == 0)
		return (false);
	if (is_valid_char(map[y - 1][x - 1]) == false)
		return (false);
	if (is_valid_char(map[y - 1][x]) == false)
		return (false);
	if (is_valid_char(map[y - 1][x + 1]) == false)
		return (false);
	if (is_valid_char(map[y][x - 1]) == false)
		return (false);
	if (is_valid_char(map[y][x + 1]) == false)
		return (false);
	if (is_valid_char(map[y + 1][x - 1]) == false)
		return (false);
	if (is_valid_char(map[y + 1][x]) == false)
		return (false);
	if (is_valid_char(map[y + 1][x + 1]) == false)
		return (false);
	return (true);
}

bool	valid_map(char **map)
{
	int		i;
	char	*current_floor;

	i = 0;
	current_floor = ft_strchr(map[i], '0');
	while (map[i])
	{
		if (current_floor)
		{
			if (check_valid_surrounding(map, current_floor, i) == false)
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
	if (valid_map(map_val))
		return (true);
	write(2, "Error: Invalid map\n", 19);
	return (false);
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
