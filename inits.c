/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia@student.42porto.pt>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:33:47 by tabreia-          #+#    #+#             */
/*   Updated: 2023/06/14 22:33:47 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	initiliaze_map(void)
{
	t_map	map;

	map.player = 0;
	map.map_size.x = 0;
	map.map_size.y = 0;
	return (map);
}