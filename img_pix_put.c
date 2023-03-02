/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_pix_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:34:55 by ssadiki           #+#    #+#             */
/*   Updated: 2023/03/01 04:25:07 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	img->addr = (int *) mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
	pixel = (char *) img->addr + (img->line_len * y + x * (img->bpp / 8));
	*(int *)pixel = color;
}
