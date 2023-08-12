/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:44:39 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/08/10 17:08:19 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"

void	draw_line(t_data *data, t_point p0, t_point p1);
void	draw_square(t_data *data, int y, int x, int color);
void	draw_square_player(t_data *data, int y, int x, int color);

#endif /* MINIMAP_H */
