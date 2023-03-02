/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:36:55 by ssadiki           #+#    #+#             */
/*   Updated: 2023/03/02 14:22:01 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floor_ceiling(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < WIN_HEIGHT / 2)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			img_pix_put(&data->img, x, y, data->ceiling_color);
	}
	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			img_pix_put(&data->img, x, y, data->floor_color);
		y++;
	}
}

void	load_textures(t_data *data)
{
	if (data->dda.side == 0 && data->dda.step_x == -1)
		data->tex.img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, \
			data->north_texture, &data->tex.tex_width, \
			&data->tex.tex_height);
	else if (data->dda.side == 0 && data->dda.step_x == 1)
		data->tex.img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, \
			data->south_texture, &data->tex.tex_width, \
			&data->tex.tex_height);
	else if (data->dda.side == 1 && data->dda.step_y == 1)
		data->tex.img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, \
			data->east_texture, &data->tex.tex_width, \
			&data->tex.tex_height);
	else if (data->dda.side == 1 && data->dda.step_y == -1)
		data->tex.img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, \
			data->west_texture, &data->tex.tex_width, \
			&data->tex.tex_height);
	data->tex.img.addr = (int *)mlx_get_data_addr(data->tex.img.mlx_img, \
			&data->tex.img.line_len, &data->tex.img.bpp, &data->tex.img.endian);
}

void	get_wall_height(t_data *data)
{
	if (data->dda.walldist == 0)
		data->dda.walldist++;
	data->tex.wall_height = (int)(WIN_HEIGHT / data->dda.walldist);
	data->tex.wall_start = -data->tex.wall_height / 2 + WIN_HEIGHT / 2;
	if (data->tex.wall_start < 0)
		data->tex.wall_start = 0;
	data->tex.wall_end = data->tex.wall_height / 2 + WIN_HEIGHT / 2;
	if (data->tex.wall_end >= WIN_HEIGHT)
		data->tex.wall_end = WIN_HEIGHT - 1;
}

void	get_tex_coord(t_data *data)
{
	double	wallx;

	if (data->dda.side == 0)
		wallx = data->p.y + data->dda.walldist * data->vec.ray_y;
	else
		wallx = data->p.x + data->dda.walldist * data->vec.ray_x;
	wallx -= (int)((wallx));
	data->tex.tex_x = (int)(wallx * (double)data->tex.tex_width);
	if (data->dda.side == 0 && data->vec.ray_x > 0)
		data->tex.tex_x = data->tex.tex_width - data->tex.tex_x - 1;
	if (data->dda.side == 1 && data->vec.ray_y < 0)
		data->tex.tex_x = data->tex.tex_width - data->tex.tex_x - 1;
	data->tex.tex_step = 1.0 * data->tex.tex_height / data->tex.wall_height;
	data->tex.tex_pos = (data->tex.wall_start - WIN_HEIGHT / 2 + \
			data->tex.wall_height / 2) * data->tex.tex_step;
}

void	render_map(t_data *data, int x)
{
	int	color;
	int	y;

	get_wall_height(data);
	get_tex_coord(data);
	y = data->tex.wall_start;
	while (y < data->tex.wall_end)
	{
		data->tex.tex_y = (int)data->tex.tex_pos & (data->tex.tex_height - 1);
		data->tex.tex_pos += data->tex.tex_step;
		color = data->tex.img.addr[data->tex.tex_height * data->tex.tex_y + \
				data->tex.tex_x];
		if (data->dda.side == 1)
			color = (color >> 1) & 8355711;
		data->img.addr[y * WIN_WIDTH + x] = color;
		y++;
	}
}
