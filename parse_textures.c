/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia@student.42porto.pt>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 01:46:08 by tabreia-          #+#    #+#             */
/*   Updated: 2023/07/29 01:46:08 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_pixel_info(t_data *data, int id)
{
	char	*str;
	char 	**info;
	int		fd;
	int 	i;

	i = 0;
	fd = open(data->file_cont->textures_path[id], O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		if (!ft_strncmp(str, "/* pixels */", ft_strlen(str)))
		{
			free(str);
			str = get_next_line(fd);
			free(str);
			break ;
		}
	}
	str = get_next_line(fd);
	while (ft_strncmp(str, "/* pixels */", ft_strlen(str)))
	{
		free(str);
		str = get_next_line(fd);
		str = ft_strtrim(str, "\"");
		info = ft_split(str, ' ');
		data->texData[id].pixelData[i].symbol = info[0][0];
		info[2] = ft_strtrim(info[2], "#");
		data->texData[id].pixelData[i].hex_color = ft_atoi(info[2]);
		i++;
	}
	close (fd);
}

int		get_n_colors(t_data *data, int id)
{
	char 	**info;
	char	*str;
	char	*nums;
	int		stop;
	int		fd;

	stop = 0;
	fd = open(data->file_cont->textures_path[id], O_RDONLY);
	str = get_next_line(fd);
	while (str && stop == 0)
	{
		free(str);
		str = get_next_line(fd);
		if (!ft_strncmp(str, "/* columns rows colors chars-per-pixel */", ft_strlen("/* columns rows colors chars-per-pixel */")))
		{
			nums = get_next_line(fd);
			nums = ft_strtrim(nums,  "\",\n");
			info = ft_split(nums, ' ');
			stop++;
			free(nums);
		}
	}
	close(fd);
	data->texData[id].columns = ft_atoi(info[0]);
	data->texData[id].rows = ft_atoi(info[1]);
	data->texData[id].n_of_colors = ft_atoi(info[2]);
	return (ft_atoi(info[2]));
}

void	parse_textures(t_data *data)
{
	char 	*info;
	char	*str;
	int		i;
	int		k;
	int		fd;

	i = 0;
	while (i < 4)
	{
		k = 0;
		fd = open(data->file_cont->textures_path[i], O_RDONLY);
		str = get_next_line(fd);
		while (ft_strncmp(str, "/* pixels */", ft_strlen("/* pixels */")))
		{
			free(str);
			str = get_next_line(fd);
		}
		while (ft_strncmp(str, "};", ft_strlen("};")))
		{
			str = get_next_line(fd);
			info = ft_strtrim(str, "\"");
			data->texData[i].tex_array[k] = ft_strdup(info);
			k++;
		}
		close(fd);
		i++;
		get_pixel_info(data, i);
	}


}