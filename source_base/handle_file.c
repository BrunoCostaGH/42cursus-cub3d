/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:49:25 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/13 15:16:21 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
 * id 0 is N texture
 * id 1 is S texture
 * id 2 is W texture
 * id 3 is E texture
 */
int	save_path_to_struct(char *str, int id, t_data *data)
{
	char	*temp[2];
	char	**info;
	int		len;

	info = ft_split(str, ' ');
	len = ft_strlen(info[1]);
	temp[1] = ft_strtrim(info[1], "\n\r");
	temp[0] = ft_strtrim(info[0], "\n\r");
	free(info[0]);
	free(info[1]);
	info[0] = temp[0];
	info[1] = temp[1];
	if (info[2])
	{
		write_invalid_format_path(info);
		return (0);
	}
	if (!check_if_file_exists(info[1], ".xpm"))
	{
		free_char_arr(info);
		return (0);
	}
	return (copy_file_path(data, info, len, id));
}

/*
 * Id 0 is for floor RGB code
 * Id 1 is for ceiling RGB code
 */
int	save_rgb_to_struct(char *str, int id, t_data *data)
{
	char	*temp[2];
	char	**info;
	char	**rgb;

	info = ft_split(str, ' ');
	temp[1] = ft_strtrim(info[1], "\n\r");
	temp[0] = ft_strtrim(info[0], "\n\r");
	free(info[0]);
	free(info[1]);
	info[0] = temp[0];
	info[1] = temp[1];
	rgb = 0;
	if (!validate_rgb(data, id, info, rgb))
		return (0);
	return (1);
}

char	**check_for_data(char **str, t_data *data)
{
	int		index[2];
	int		beg_map;

	beg_map = find_identifiers(str, data);
	if (beg_map == -2)
		return (0);
	else if (beg_map == -1)
	{
		if (!is_valid_struct(data))
			write(2, "Error: Missing identifier\n", 26);
		else
			write(2, "Error: Missing map\n", 19);
		return (0);
	}
	data->file_cont->map_arr = get_map(beg_map, str);
	index[0] = 0;
	while (data->file_cont->map_arr[++index[0] - 1])
	{
		index[1] = 0;
		while (data->file_cont->map_arr[index[0] - 1][++index[1] - 1])
			if (is_valid_char(data->file_cont->map_arr[index[0] - 1] \
					[index[1] - 1], true))
				data->file_cont->map_arr[index[0] - 1][index[1] - 1] = '0';
	}
	return (get_map(beg_map, str));
}

int	count_lines(char *file_path)
{
	int		lines;
	int		fd;
	char	*str;

	lines = 0;
	fd = open(file_path, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		lines++;
	}
	close(fd);
	return (lines);
}

int	read_file(char *file_path, t_data *data)
{
	int		fd;
	int		lines;
	char	*str;
	int		i;

	i = -1;
	lines = count_lines(file_path);
	if (lines <= 0)
	{
		write_empty_file(file_path);
		return (0);
	}
	data->file_cont->txt = ft_calloc(lines + 1, sizeof(char *));
	fd = open(file_path, O_RDONLY);
	while (i++ < lines)
	{
		str = get_next_line(fd);
		if (str)
			data->file_cont->txt[i] = ft_strdup(str);
		free(str);
	}
	close(fd);
	return (1);
}
