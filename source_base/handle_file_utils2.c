/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia@student.42porto.pt>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:58:32 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/13 14:05:18 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_rgb_range(char **rgb)
{
	int	index[2];
	int	red;
	int	green;
	int	blue;

	index[0] = 0;
	while (index[0] <= 2 && rgb[index[0]])
	{
		index[1] = 0;
		while (rgb[index[0]][index[1]])
			if (!ft_isdigit(rgb[index[0]][index[1]++]))
				return (0);
		index[0]++;
	}
	red = ft_atoi(rgb[0]);
	green = ft_atoi(rgb[1]);
	blue = ft_atoi(rgb[2]);
	if ((red >= 0 && red <= 255) && (green >= 0 && green <= 255) && \
		(blue >= 0 && blue <= 255))
	{
		return (1);
	}
	return (0);
}

int	save_values(t_data *data, int id, char **rgb, char **info)
{
	if (!data->file_cont->colors[id])
	{
		data->file_cont->colors[id] = ft_calloc(3 + 1, sizeof(int));
		data->file_cont->colors[id][0] = ft_atoi(rgb[0]);
		data->file_cont->colors[id][1] = ft_atoi(rgb[1]);
		data->file_cont->colors[id][2] = ft_atoi(rgb[2]);
		free_char_arr(info);
		free_char_arr(rgb);
		return (1);
	}
	return (0);
}

int	copy_file_path(t_data *data, char **info, int len, int id)
{
	if (!data->file_cont->textures_path[id])
	{
		data->file_cont->textures_path[id] = ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(data->file_cont->textures_path[id], info[1], len);
		free_char_arr(info);
		return (1);
	}
	return (0);
}

int	validate_rgb(t_data *data, int id, char **info, char **rgb)
{
	if (info[2])
	{
		write_invalid_format_rgb(info);
		return (0);
	}
	rgb = ft_split(info[1], ',');
	if (rgb && (!rgb[0] || !rgb[1] || !rgb[2]))
	{
		write_miss_rgb(info, rgb);
		return (0);
	}
	if (rgb && !(check_rgb_range(rgb)))
	{
		write_out_of_range(info, rgb);
		return (0);
	}
	return (rgb && save_values(data, id, rgb, info));
}
