/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:31:42 by ssadiki           #+#    #+#             */
/*   Updated: 2023/03/01 02:49:05 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	up_down(t_data *data)
{
	if (data->kp.up == 1)
	{
		if (map[(int)(data->p.x + data->p.dir_x * data->p.move_speed)] \
				[(int)data->p.y] == 0)
			data->p.x += data->p.dir_x * data->p.move_speed;
		if (map[(int)data->p.x] \
				[(int)(data->p.y + data->p.dir_y * data->p.move_speed)] == 0)
			data->p.y += data->p.dir_y * data->p.move_speed;
	}
	else if (data->kp.down == 1)
	{
		if (map[(int)(data->p.x - data->p.dir_x * data->p.move_speed)] \
				[(int)data->p.y] == 0)
			data->p.x -= data->p.dir_x * data->p.move_speed;
		if (map[(int)data->p.x] \
				[(int)(data->p.y - data->p.dir_y * data->p.move_speed)] == 0)
			data->p.y -= data->p.dir_y * data->p.move_speed;
	}
}

void	left_right(t_data *data)
{
	if (data->kp.left == 1)
	{
		if (map[(int)(data->p.x - data->vec.plane_x * data->p.move_speed)] \
				[(int)data->p.y] == 0)
			data->p.x -= data->vec.plane_x * data->p.move_speed * \
				data->p.direction;
		if (map[(int)data->p.x] \
				[(int)(data->p.y - data->vec.plane_y * data->p.move_speed)] == 0)
			data->p.y -= data->vec.plane_y * data->p.move_speed * \
				data->p.direction;
	}
	else if (data->kp.right == 1)
	{
		if (map[(int)(data->p.x + data->vec.plane_x * data->p.move_speed)] \
				[(int)data->p.y] == 0)
			data->p.x += data->vec.plane_x * data->p.move_speed * \
				data->p.direction;
		if (map[(int)data->p.x] \
				[(int)(data->p.y + data->vec.plane_y * data->p.move_speed)] == 0)
			data->p.y += data->vec.plane_y * data->p.move_speed * \
				data->p.direction;
	}
}

void	rotate(t_data *data, double rotation_speed)
{
	double	tmpdir;
	double	tmpplane;

	tmpdir = data->p.dir_x;
	tmpplane = data->vec.plane_x;
	data->p.dir_x = data->p.dir_x * cos(rotation_speed) - \
			data->p.dir_y * sin(rotation_speed);
	data->p.dir_y = tmpdir * sin(rotation_speed) + \
			data->p.dir_y * cos(rotation_speed);
	data->vec.plane_x = data->vec.plane_x * cos(rotation_speed) - \
			data->vec.plane_y * sin(rotation_speed);
	data->vec.plane_y = tmpplane * sin(rotation_speed) + \
			data->vec.plane_y * cos(rotation_speed);
}
