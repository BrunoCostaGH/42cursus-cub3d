/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:11:33 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/10 19:29:04 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handle_mouse_2(t_data *data)
{
	if (!data->moves.ctrl && data->mouse.y > data->old_mouse.y)
	{
		data->moves.r_down = true;
		data->diff_y = data->mouse.y - data->old_mouse.y;
	}
	if (!data->moves.ctrl && data->mouse.y < data->old_mouse.y)
	{
		data->moves.r_up = true;
		data->diff_y = data->old_mouse.y - data->mouse.y;
	}
	if (data->mouse.y == data->old_mouse.y)
	{
		data->moves.r_up = false;
		data->moves.r_down = false;
	}
}

int	handle_mouse(t_data *data)
{
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &data->mouse.x, \
		&data->mouse.y);
	if (!data->moves.ctrl && data->mouse.x > data->old_mouse.x)
	{
		data->moves.r_right_mouse = true;
		data->diff_x = data->mouse.x - data->old_mouse.x;
	}
	if (!data->moves.ctrl && data->mouse.x < data->old_mouse.x)
	{
		data->moves.r_left_mouse = true;
		data->diff_x = data->old_mouse.x - data->mouse.x;
	}
	if (data->mouse.x == data->old_mouse.x)
	{
		data->moves.r_right_mouse = false;
		data->moves.r_left_mouse = false;
	}
	handle_mouse_2(data);
	if (!data->moves.ctrl)
		mlx_mouse_move(data->mlx_ptr, data->win_ptr, data->window.x / 2, \
			data->window.y / 2);
	return (0);
}

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
	if (key == XK_Control_L || key == XK_Control_R)
	{
		data->moves.ctrl = false;
		mlx_mouse_move(data->mlx_ptr, data->win_ptr, data->window.x / 2, \
			data->window.y / 2);
		mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
	}
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
	if (key == XK_Control_L || key == XK_Control_R)
	{
		data->moves.ctrl = true;
		mlx_mouse_move(data->mlx_ptr, data->win_ptr, data->window.x / 2, \
			data->window.y / 2);
		mlx_mouse_show(data->mlx_ptr, data->win_ptr);
	}
	if (key == XK_Escape)
		free_game(data);
	return (0);
}
