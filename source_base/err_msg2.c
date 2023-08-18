/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia@student.42porto.pt>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:21:48 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/13 14:53:51 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	write_empty_file(char *file_path)
{
	write(2, "Error: `", 8);
	if (file_path)
		write(2, file_path, ft_strlen(file_path));
	write(2, "': Empty file\n", 14);
}
