/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia@student.42porto.pt>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:23:44 by tabreia-          #+#    #+#             */
/*   Updated: 2023/07/01 15:53:28 by bsilva-c         ###   ########.fr       */
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

/*void	flood_fill(char **map_val, int y, int x)
{
	if (map_val[y][x] == 'F' || (map_val[y][x] != '0' && map_val[y][x] != 'C'\
		&& map_val[y][x] != 'E' && map_val[y][x] != 'P'))
		return ;
	map_val[y][x] = 'F';
	flood_fill(map_val, y - 1, x);
	flood_fill(map_val, y + 1, x);
	flood_fill(map_val, y, x - 1);
	flood_fill(map_val, y, x + 1);
}*/

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

void	check_perimeter(char **map,int y, int x, t_data *data)
{
	if (y < 0 || y > data->max.y || x < 0 || x > ft_strlen(map[y]))
		return ;
	if (map[y][x] == 'F' || (map[y][x] != '1'))
		return ;
	if (y == data->flood_point.y && x == data->flood_point.x)
		data->map_sur = 1;
	map[y][x] = 'F';
	if (y <= data->max.y / 2)
	{
		check_perimeter(map, y, x + 1, data);
		check_perimeter(map, y + 1, x, data);
		check_perimeter(map, y - 1, x, data);
		if (y != 0)
			check_perimeter(map, y, x - 1, data);
	}
	else
	{
		check_perimeter(map, y, x - 1, data);
		check_perimeter(map, y - 1, x, data);
		check_perimeter(map, y + 1, x, data);
		check_perimeter(map, y, x + 1, data);
	}
}


bool valid_map(char **arr, t_data *data)
{
	get_max_yx(arr, data);
	get_start_point(arr, data);
	check_perimeter(arr, data->flood_point.y, data->flood_point.x + 1, data);
	if (data->map_sur == 1)
		return (true);
	return (false);
}

bool valid_cub_file(char *file_path, t_data *data)
{
	char	**map_val;

	if (read_file(file_path, data) == 0)
		return (false);
	map_val = check_for_data(data->file_cont->txt, data);
	if (valid_map(map_val, data))
		return (true);
	return (false);
}

bool check_if_file_exists(char *file_path, int is_cub_file)
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
