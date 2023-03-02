/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:15:39 by ssadiki           #+#    #+#             */
/*   Updated: 2023/03/01 04:07:32 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw(t_data *data)
{
	double	camerax;
	int		x;

	if (!data->win_ptr)
		return (1);
	floor_ceiling(data);
	x = 0;
	while (x < WIN_WIDTH)
	{
		camerax = 2 * x / (double)WIN_WIDTH - 1;
		data->vec.ray_x = data->p.dir_x + data->vec.plane_x * camerax;
		data->vec.ray_y = data->p.dir_y + data->vec.plane_y * camerax;
		dda(data);
		load_textures(data);
		render_map(data, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
		data->img.mlx_img, 0, 0);
	return (0);
}
