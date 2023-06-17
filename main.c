/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia@student.42porto.pt>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:27:42 by tabreia-          #+#    #+#             */
/*   Updated: 2023/06/17 18:40:39 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_struct(t_data *data)
{
	int i = 0;
	int k = 0;

	while (data->file_cont->textures[i])
	{
		printf("%s\n", data->file_cont->textures[i]);
		i++;
	}
	i = 0;
	while (data->file_cont->colors[i])
	{
		k = 0;
		while (data->file_cont->colors[i][k])
		{
			printf("%i\n", data->file_cont->colors[i][k]);
			k++;
		}
		i++;
	}
	i = 0;
	k = 0;
	while (data->file_cont->map_arr[i])
	{
		printf("%s", data->file_cont->map_arr[i]);
		i++;
	}
	/*i = 0;
	while (i <= 5)
	{
		printf("%i ffx\n", data->flood_points[i].x);
		printf("%i ffy\n", data->flood_points[i].y);
		i++;
	}*/
}

t_data	*generate_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->mlx_ptr = 0;
	data->win_ptr = 0;
	data->map_sur = 0;
	data->img.mlx_img = 0;
	data->file_cont = malloc(sizeof(t_file));
	data->file_cont->textures = malloc(sizeof(char *) * 4);
	data->file_cont->colors = malloc(sizeof(int *) * 3);
	return (data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2 || !check_if_file_exists(av[1], 1))
		return (1);
	data = generate_data();
	if (validate_cub_file(av[1], data))
	{
		write(2, "Error: Invalid .cub file\n", 25);
		return (1);
	}
	start_game(data);
	print_struct(data);
}
