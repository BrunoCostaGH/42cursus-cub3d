/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:27:42 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/08 17:43:44 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*generate_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->mlx_ptr = 0;
	data->win_ptr = 0;
	init_moves(data);
	init_images(data);
	init_file_cont(data);
	data->window.x = 1280;
	data->window.y = 1024;
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
	start_game(data);
}
