/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:31:27 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/08 19:31:27 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	run_compares(char *str, t_data *data)
{
	if (!ft_strncmp(str, "NO", 2) && save_path_to_struct(str, 0, data))
		return (1);
	else if (!ft_strncmp(str, "SO", 2) && save_path_to_struct(str, 1, data))
		return (1);
	else if (!ft_strncmp(str, "WE", 2) && save_path_to_struct(str, 2, data))
		return (1);
	else if (!ft_strncmp(str, "EA", 2) && save_path_to_struct(str, 3, data))
		return (1);
	else if (!ft_strncmp(str, "F", 1) && save_rgb_to_struct(str, 0, data))
		return (1);
	else if (!ft_strncmp(str, "C", 1) && save_rgb_to_struct(str, 1, data))
		return (1);
	return (0);
}

int	find_identifiers(char **str, t_data *data)
{
	int	i;
	int	beg_map;

	i = 0;
	beg_map = -1;
	while (str[i])
	{
		if (!run_compares(str[i], data) && !is_empty_line(str[i]) && \
		beg_map == -1 && is_valid_struct(data))
			beg_map = i;
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
	while (txt[beg_map])
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
				data->file_cont->textures_path[2])
		if (data->file_cont->colors[0] && data->file_cont->colors[1])
			return (true);
	return (false);
}
