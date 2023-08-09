/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia@student.42porto.pt>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:58:32 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/09 17:58:32 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_rgb_range(char **rgb)
{
	int	red;
	int	green;
	int	blue;

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

void	save_values(t_data *data, int id, char **rgb, char **info)
{
	data->file_cont->colors[id] = ft_calloc(3 + 1, sizeof(int));
	data->file_cont->colors[id][0] = ft_atoi(rgb[0]);
	data->file_cont->colors[id][1] = ft_atoi(rgb[1]);
	data->file_cont->colors[id][2] = ft_atoi(rgb[2]);
	free_char_arr(info);
	free_char_arr(rgb);
}

void	copy_file_path(t_data *data, char **info, int len, int id)
{
	data->file_cont->textures_path[id] = ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(data->file_cont->textures_path[id], info[1], len);
	free_char_arr(info);
}

int	validate_rgb(t_data *data, int id, char **info, char **rgb)
{
	if (info[2])
	{
		write_invalid_format_rgb(info);
		return (0);
	}
	rgb = ft_split(info[1], ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		write_miss_rgb(info, rgb);
		return (0);
	}
	if (!(check_rgb_range(rgb)))
	{
		write_out_of_range(info, rgb);
		return (0);
	}
	save_values(data, id, rgb, info);
	return (1);
}
