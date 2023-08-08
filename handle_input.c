/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:11:33 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/08 18:11:33 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key_release(int key, t_data *data)
{
	if (key == XK_w)
		data->moves.forward = false;
	if (key == XK_s)
		data->moves.back = false;
	if (key == XK_d)
		data->moves.right = false;
	if (key == XK_a)
		data->moves.left = false;
	if (key == XK_Left)
		data->moves.r_left = false;
	if (key == XK_Right)
		data->moves.r_right = false;
	return (0);
}

int	handle_keypress(int key, t_data *data)
{
	if (key == XK_w)
		data->moves.forward = true;
	if (key == XK_s)
		data->moves.back = true;
	if (key == XK_d)
		data->moves.right = true;
	if (key == XK_a)
		data->moves.left = true;
	if (key == XK_Left)
		data->moves.r_left = true;
	if (key == XK_Right)
		data->moves.r_right = true;
	if (key == XK_Escape)
		free_game(data);
	return (0);
}
