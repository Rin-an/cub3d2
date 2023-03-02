/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:40:24 by ssadiki           #+#    #+#             */
/*   Updated: 2023/03/01 16:15:08 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_delta(t_data *data)
{
	if (data->vec.ray_x == 0)
		data->dda.dx = 1e30;
	else
		data->dda.dx = fabs(1 / data->vec.ray_x);
	if (data->vec.ray_y == 0)
		data->dda.dy = 1e30;
	else
		data->dda.dy = fabs(1 / data->vec.ray_y);
}

void	init_dda(t_data *data)
{
	data->dda.map_x = (int) data->p.x;
	data->dda.map_y = (int) data->p.y;
	set_delta(data);
	if (data->vec.ray_x < 0)
	{
		data->dda.step_x = -1;
		data->dda.sidedist_x = (data->p.x - data->dda.map_x) * data->dda.dx;
	}
	else
	{
		data->dda.step_x = 1;
		data->dda.sidedist_x = (data->dda.map_x + 1 - data->p.x) * data->dda.dx;
	}
	if (data->vec.ray_y < 0)
	{
		data->dda.step_y = -1;
		data->dda.sidedist_y = (data->p.y - data->dda.map_y) * data->dda.dy;
	}
	else
	{
		data->dda.step_y = 1;
		data->dda.sidedist_y = (data->dda.map_y + 1 - data->p.y) * data->dda.dy;
	}
}

void	dda(t_data *data)
{
	int	hit;

	hit = 0;
	init_dda(data);
	while (!hit)
	{
		if (data->dda.sidedist_x < data->dda.sidedist_y)
		{
			data->dda.side = 0;
			data->dda.sidedist_x += data->dda.dx;
			data->dda.map_x += data->dda.step_x;
		}
		else
		{
			data->dda.side = 1;
			data->dda.sidedist_y += data->dda.dy;
			data->dda.map_y += data->dda.step_y;
		}
		if (data->map[data->dda.map_x][data->dda.map_y] != '0')
			hit = 1;
	}
	if (data->dda.side == 0)
		data->dda.walldist = data->dda.sidedist_x - data->dda.dx;
	else
		data->dda.walldist = data->dda.sidedist_y - data->dda.dy;
}
