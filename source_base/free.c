/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:12:41 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/10 17:58:23 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_int_arr(int **info)
{
	int	i;

	i = 0;
	while (info[i])
	{
		free(info[i]);
		i++;
	}
	free(info);
	info = 0;
}

void	free_char_arr(char **info)
{
	int	i;

	i = 0;
	while (info[i])
	{
		free(info[i]);
		i++;
	}
	free(info);
	info = 0;
}

void	free_extra(t_data *data)
{
	if (data->mini->mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->mini->mlx_img);
	free(data->mini);
	if (data->prev_mini->mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->prev_mini->mlx_img);
	free(data->prev_mini);
}

void	free_file_cont(t_data *data)
{
	free_char_arr(data->file_cont->map_arr);
	free_char_arr(data->file_cont->txt);
	free_char_arr(data->file_cont->textures_path);
	free_int_arr(data->file_cont->colors);
	free(data->file_cont);
	free_extra(data);
}

int	free_game(t_data *data)
{
	int	i;

	if (data->img->mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->tex_img)
	{
		i = 0;
		while (data->tex_img[i])
		{
			mlx_destroy_image(data->mlx_ptr, data->tex_img[i]->mlx_img);
			free(data->tex_img[i++]);
		}
		free(data->tex_img);
	}
	free_file_cont(data);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free(data->img);
	free(data);
	exit(0);
}
