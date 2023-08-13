/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:31:27 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/13 15:06:46 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	run_compares(char *a_str, t_data *data)
{
	char	**str_arr;
	char	*str;
	int		status;

	str_arr = ft_split(a_str, ' ');
	str = str_arr[0];
	status = 0;
	if (str)
	{
		if ((!ft_strncmp(str, "NO", 3) && save_path_to_struct(a_str, 0, data)) \
		|| (!ft_strncmp(str, "SO", 3) && save_path_to_struct(a_str, 1, data)) \
		|| (!ft_strncmp(str, "WE", 3) && save_path_to_struct(a_str, 2, data)) \
		|| (!ft_strncmp(str, "EA", 3) && save_path_to_struct(a_str, 3, data)) \
		|| (!ft_strncmp(str, "F", 2) && save_rgb_to_struct(a_str, 0, data)) || \
		(!ft_strncmp(str, "C", 2) && save_rgb_to_struct(a_str, 1, data)))
			status = 1;
		else if (str[0] && ft_isalpha(str[0]))
		{
			write(2, "Error: Duplicate or invalid identifier\n", 39);
			status = 2;
		}
	}
	free_char_arr(str_arr);
	return (status);
}

int	find_identifiers(char **str, t_data *data)
{
	int	i;
	int	beg_map;
	int	status;

	i = 0;
	beg_map = -1;
	status = 0;
	while (str[i] && status != 2)
	{
		if (!is_empty_line(str[i]))
		{
			status = run_compares(str[i], data);
			if (!status)
			{
				if (is_valid_struct(data) && beg_map == -1)
					beg_map = i;
			}
			else if (status == 2)
				beg_map = -2;
		}
		i++;
	}
	return (beg_map);
}

char	**get_map(int beg_map, char **txt)
{
	int		i;
	char	**map;

	i = 0;
	while (txt[i])
		i++;
	map = ft_calloc(i - beg_map + 1, sizeof(char *));
	i = 0;
	while (beg_map >= 0 && txt[beg_map] && txt[beg_map][0])
		map[i++] = ft_strdup(txt[beg_map++]);
	return (map);
}

bool	is_empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (ft_isprint(str[i++]))
			return (false);
	return (true);
}

bool	is_valid_struct(t_data *data)
{
	if (data->file_cont->textures_path[0] && \
			data->file_cont->textures_path[1] && \
				data->file_cont->textures_path[2] && \
					data->file_cont->textures_path[3])
		if (data->file_cont->colors[0] && data->file_cont->colors[1])
			return (true);
	return (false);
}
