/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:56:23 by tabreia-          #+#    #+#             */
/*   Updated: 2023/08/12 17:13:30 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_dir_vector(t_data *data)
{
	if ('N' == data->player.init_dir)
		set_n(data);
	if ('S' == data->player.init_dir)
		set_s(data);
	if ('E' == data->player.init_dir)
		set_e(data);
	if ('W' == data->player.init_dir)
		set_w(data);
}

int	handle_movement(t_data *data)
{
	double	move_speed;
	double	rot_speed_x;
	double	rot_speed_y;

	move_speed = 0.1;
	rot_speed_x = move_speed + (move_speed * (data->diff_x / 40));
	rot_speed_y = move_speed + (move_speed * data->diff_y * 40);
	init_minimap(data);
	if (data->moves.forward == true)
		move_forward(data, move_speed);
	if (data->moves.back == true)
		move_backwards(data, move_speed);
	if (data->moves.left == true)
		move_left(data, move_speed);
	if (data->moves.right == true)
		move_right(data, move_speed);
	if (data->moves.r_left == true || data->moves.r_left_mouse == true)
		rotate_left(data, rot_speed_x);
	if (data->moves.r_right == true || data->moves.r_right_mouse == true)
		rotate_right(data, rot_speed_x);
	if (data->moves.r_up == true)
		rotate_up(data, rot_speed_y);
	if (data->moves.r_down == true)
		rotate_down(data, rot_speed_y);
	return (0);
}

void	start_game(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window.x, data->window \
	.y, "cub3d");
	data->ray.pos_x = data->player.init_pos.x + 0.5;
	data->ray.pos_y = data->player.init_pos.y + 0.5;
	get_dir_vector(data);
	load_textures(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, \
		&handle_keypress, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, \
		&handle_key_release, data);
	mlx_hook(data->win_ptr, 17, 1L << 17, free_game, data);
	mlx_loop_hook(data->mlx_ptr, &raycast, data);
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr, data->window.x / 2, \
		data->window.y / 2);
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &data->old_mouse.x, \
		&data->old_mouse.y);
	mlx_loop(data->mlx_ptr);
}
