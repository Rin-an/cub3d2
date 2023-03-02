/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:12:11 by ssadiki           #+#    #+#             */
/*   Updated: 2023/03/01 04:46:54 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	reset_settings(t_data *data)
{
	data->p.x = 1;
	data->p.y = 1;
	data->p.dir_x = -1;
	data->p.dir_y = 0;
	data->vec.plane_y = 0.66;
	data->vec.plane_x = 0;
}

int	keypress(int keycode, t_data *data)
{
	if (keycode == 53)
		exit_keypress(data);
	else if (keycode == 13)
		data->kp.up = 1;
	else if (keycode == 1)
		data->kp.down = 1;
	else if (keycode == 0)
		data->kp.left = 1;
	else if (keycode == 2)
		data->kp.right = 1;
	else if (keycode == 123)
		data->kp.r_left = 1;
	else if (keycode == 124)
		data->kp.r_right = 1;
	else if (keycode == 15)
		data->kp.reset = 1;
	else
		return (1);
	move_player(data);
	return (0);
}

int	keyrelease(int keycode, t_data *data)
{
	if (keycode == 13)
		data->kp.up = 0;
	else if (keycode == 1)
		data->kp.down = 0;
	else if (keycode == 0)
		data->kp.left = 0;
	else if (keycode == 2)
		data->kp.right = 0;
	else if (keycode == 123)
		data->kp.r_left = 0;
	else if (keycode == 124)
		data->kp.r_right = 0;
	else if (keycode == 15)
		data->kp.reset = 0;
	return (0);
}

void	move_player(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (data->kp.up || data->kp.down)
		up_down(data);
	else if (data->kp.right || data->kp.left)
		left_right(data);
	else if (data->kp.r_right)
		rotate(data, -data->p.rotation_speed);
	else if (data->kp.r_left)
		rotate(data, data->p.rotation_speed);
	else if (data->kp.reset)
		reset_settings(data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
}

void	hooks(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 0, &keypress, data);
	mlx_hook(data->win_ptr, 3, 0, &keyrelease, data);
	mlx_hook(data->win_ptr, 17, 0, &exit_button, data);
}
