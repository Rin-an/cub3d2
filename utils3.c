/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:34:55 by ssadiki           #+#    #+#             */
/*   Updated: 2023/03/02 22:26:32 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	player_check(char c, int *existence, t_data *mlx, t_point point)
{
	if (ft_strchr("NSWE", c) != NULL)
	{
		if (*existence == 1)
			return (1);
		else
		{
			(*existence) = 1;
			mlx->p.x = point.j;
			mlx->p.y = point.i;
		}
	}
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	img->addr = (int *) mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
	pixel = (char *) img->addr + (img->line_len * y + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	ft_strlenew(char **s)
{
	size_t	i;

	i = 0;
	(*s) = ft_strtrim(*s, " \n");
	while ((*s)[i])
		i++;
	return (i);
}
