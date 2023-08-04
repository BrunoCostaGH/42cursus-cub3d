/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:27:42 by tabreia-          #+#    #+#             */
/*   Updated: 2023/07/06 15:08:59 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_struct(t_data *data)
{
	int	i;
	int	k;

	printf("map_size.x: %d\nmap_size.y: %d\n", data->file_cont->map_size.x, \
	data->file_cont->map_size.y);
	i = 0;
	while (data->file_cont->textures_path[i])
		printf("%s\n", data->file_cont->textures_path[i++]);
	i = 0;
	while (data->file_cont->colors[i])
	{
		k = 0;
		while (data->file_cont->colors[i][k])
			printf("%i\n", data->file_cont->colors[i][k++]);
		i++;
	}
	i = 0;
	while (data->file_cont->map_arr[i])
		printf("%s", data->file_cont->map_arr[i++]);
	/*i = 0;
	while (i <= 5)
	{
		printf("%i ffx\n", data->flood_points[i].x);
		printf("%i ffy\n", data->flood_points[i].y);
		i++;
	}*/
}

void	generate_texture_data(t_data *data)
{
	int	i;
	int	k;
	int	n_colors;

	i = 0;
	data->texData = malloc(sizeof (t_texData) * 4);
	while (i < 4)
	{
		k = 0;
		n_colors = get_n_colors(data, i);
		data->texData[i].tex_colors = malloc(sizeof(int) * n_colors);
		data->texData[i].tex_symbols = malloc(sizeof(char) * n_colors);
		data->texData[i].tex_array = malloc(sizeof(char *) * data->texData->rows);
		while (k < data->texData->rows)
		{
			data->texData[i].tex_array[k] = malloc(sizeof(char) * data->texData->columns);
			k++;
		}
		i++;
		data->texData[i].pixelData = malloc(sizeof(t_pixelData) * n_colors);
	}
}

t_data	*generate_data(void)
{
	t_data	*data;
	int		i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->mlx_ptr = 0;
	data->win_ptr = 0;
	data->player.init_dir = 0;
	data->moves.right = false;
	data->moves.left = false;
	data->moves.forward = false;
	data->moves.back = false;
	data->moves.r_right = false;
	data->moves.r_left = false;
	data->window.x = 1280;
	data->window.y = 1024;
	data->file_cont = malloc(sizeof(t_file));
	data->img = malloc((sizeof(t_img)));
	data->img->mlx_img = 0;
	data->tex_img = ft_calloc(4 + 1, sizeof(t_img *));
	while (i < 4)
	{
		data->tex_img[i] = malloc(sizeof(t_img));
		data->tex_img[i]->mlx_img = 0;
		i++;
	}
	data->file_cont->map_arr = 0;
	data->file_cont->map_size.x = 0;
	data->file_cont->map_size.y = 0;
	data->file_cont->textures_path = ft_calloc(4 + 1, sizeof(char *));
	data->file_cont->colors = ft_calloc(3 + 1, sizeof(int *));
	return (data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		write(2, "Usage: ./cub3d <path_to_cub_file>\n", 34);
	if (ac != 2 || !check_if_file_exists(av[1], 1))
		return (1);
	data = generate_data();
	if (!valid_cub_file(av[1], data))
	{
		write(2, "Error: Invalid .cub file\n", 25);
		return (1);
	}
	//generate_texture_data(data);
	//parse_textures(data);
	//print_struct(data);
	start_game(data);
}
