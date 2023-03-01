/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 23:13:15 by ssadiki           #+#    #+#             */
/*   Updated: 2023/03/01 03:09:57 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_dir(t_data *data)
{
	if (map[(int) data->p.x][(int) data->p.y] == 'E')
	{
		data->p.dir_x = 0.0;
		data->p.dir_y = 1.0;
	}
	else if (map[(int) data->p.x][(int) data->p.y] == 'W')
	{
		data->p.dir_x = 0.0;
		data->p.dir_y = -1.0;
		data->p.direction = -1;
	}
	else if (map[(int) data->p.x][(int) data->p.y] == 'S')
	{
		data->p.dir_x = 1.0;
		data->p.dir_y = 0.0;
		data->p.direction = -1;
	}
	else if (map[(int) data->p.x][(int) data->p.y] == 'N')
	{
		data->p.dir_x = -1.0;
		data->p.dir_y = 0.0;
	}
}

void	set_plane(t_data *data)
{
	if (data->p.dir_x == 0)
	{
		data->vec.plane_x = 0.66;
		data->vec.plane_y = 0;
	}
	else
	{
		data->vec.plane_x = 0;
		data->vec.plane_y = 0.66;
	}
}

void	init_settings(t_data *data)
{
	data->p.x = 22;
	data->p.y = 12;
	data->kp.up = 0;
	data->kp.down = 0;
	data->kp.left = 0;
	data->kp.right = 0;
	data->kp.r_right = 0;
	data->kp.r_left = 0;
	data->kp.reset = 0;
	data->p.direction = 1;
	data->p.move_speed = 0.4;
	data->p.rotation_speed = 3.0 * (M_PI / 180);
	set_dir(data);
	set_plane(data);
	map[(int) data->p.x][(int) data->p.y] = 0;
}

void	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit(EXIT_FAILURE);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, \
		WIN_HEIGHT, "cub3d");
	if (!data->win_ptr)
		exit(EXIT_FAILURE);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = (int *)mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
}
