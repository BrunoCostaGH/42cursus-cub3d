/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:49:25 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/09 15:59:34 by bsilva-c         ###   ########.fr       */
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
		write(2, "Error: Invalid format for texture path\n", 39);
		write(2, "\tCorrect format is <NO/SO/WE/EA> <texture_path>\n", 48);
		free_char_arr(info);
		return (0);
	}
	if (!check_if_file_exists(info[1], 0))
	{
		free_char_arr(info);
		return (0);
	}
	data->file_cont->textures_path[id] = ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(data->file_cont->textures_path[id], info[1], len);
	free_char_arr(info);
	return (1);
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
	if (info[2])
	{
		free_char_arr(info);
		write(2, "Error: Invalid format for RGB\n", 30);
		write(2, "\tCorrect format is <F/C> <R,G,B>\n", 33);
		return (0);
	}
	rgb = ft_split(info[1], ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		free_char_arr(info);
		free_char_arr(rgb);
		write(2, "Error: Missing RGB value[s]\n", 28);
		return (0);
	}
	if (!((ft_atoi(rgb[0]) >= 0 && ft_atoi(rgb[0]) <= 255) || \
	(ft_atoi(rgb[1]) >= 0 && ft_atoi(rgb[1]) <= 255) || \
	(ft_atoi(rgb[2]) >= 0 && ft_atoi(rgb[2]) <= 255)))
	{
		free_char_arr(info);
		free_char_arr(rgb);
		write(2, "Error: RGB values out of range\n", 31);
		return (0);
	}
	data->file_cont->colors[id] = ft_calloc(3 + 1, sizeof(int));
	data->file_cont->colors[id][0] = ft_atoi(rgb[0]);
	data->file_cont->colors[id][1] = ft_atoi(rgb[1]);
	data->file_cont->colors[id][2] = ft_atoi(rgb[2]);
	free_char_arr(info);
	free_char_arr(rgb);
	return (1);
}

char	**check_for_data(char **str, t_data *data)
{
	int		index[2];
	int		beg_map;
	char	**map_val;

	beg_map = find_identifiers(str, data);
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
	map_val = get_map(beg_map, str);
	return (map_val);
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
		write(2, "Error: ", 7);
		write(2, file_path, ft_strlen(file_path));
		write(2, ": File is empty\n", 15);
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
