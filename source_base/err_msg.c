/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia@student.42porto.pt>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:46:36 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/13 14:51:05 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	write_invalid_format_rgb(char **info)
{
	free_char_arr(info);
	write(2, "Error: Invalid format for RGB\n", 30);
	write(2, "\tCorrect format is <F/C> <R,G,B>\n", 33);
}

void	write_miss_rgb(char **info, char **rgb)
{
	free_char_arr(info);
	free_char_arr(rgb);
	write(2, "Error: Missing RGB value[s]\n", 28);
}

void	write_out_of_range(char **info, char **rgb)
{
	free_char_arr(info);
	free_char_arr(rgb);
	write(2, "Error: RGB values out of range\n", 31);
}

void	write_invalid_format_path(char **info)
{
	free_char_arr(info);
	write(2, "Error: Invalid format for texture path\n", 39);
	write(2, "\tCorrect format is <NO/SO/WE/EA> <texture_path>\n", 48);
}

void	write_invalid_extension(char *file_ext)
{
	write(2, "Error: `", 8);
	if (file_ext)
		write(2, file_ext, ft_strlen(file_ext));
	write(2, "': Is not a valid extension\n", 28);
}
