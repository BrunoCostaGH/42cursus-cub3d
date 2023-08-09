/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia@student.42porto.pt>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:21:48 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/09 18:21:48 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	write_empty_file(char *file_path)
{
	write(2, "Error: ", 7);
	write(2, file_path, ft_strlen(file_path));
	write(2, " file is empty\n", 15);
}
