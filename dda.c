/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:40:24 by ssadiki           #+#    #+#             */
/*   Updated: 2023/02/25 15:40:42 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void  dda(t_data *data, double rayX, double rayY)
{
    int     stepX;
    int     stepY;
    int     hit;

    hit = 0;
    data->dda.mapX = (int) data->p.x;
    data->dda.mapY = (int) data->p.y;
    if (rayX == 0)
        data->dda.dx = 1e30;
    else
        data->dda.dx = fabs(1 / rayX);
    if (rayY == 0)
        data->dda.dy = 1e30;
    else
        data->dda.dy = fabs(1 / rayY);
    if (rayX < 0)
    {
        stepX = -1;
        data->dda.sideDistX = (data->p.x - data->dda.mapX ) * data->dda.dx;
    }
    else
    {
        stepX = 1;
        data->dda.sideDistX = (data->dda.mapX + 1 - data->p.x) * data->dda.dx;
    }
    if (rayY < 0)
    {
        stepY = -1;
        data->dda.sideDistY = (data->p.y - data->dda.mapY ) * data->dda.dy;
    }
    else
    {
        stepY = 1;
        data->dda.sideDistY = (data->dda.mapY + 1 - data->p.y) * data->dda.dy;
    }
    while (!hit)
    {
        if (data->dda.sideDistX < data->dda.sideDistY)
        {
            data->dda.side = 0;
            data->dda.sideDistX += data->dda.dx;
            data->dda.mapX += stepX;
        }
        else
        {
            data->dda.side = 1;
            data->dda.sideDistY += data->dda.dy;
            data->dda.mapY += stepY;
        }
        if (map[data->dda.mapX][data->dda.mapY] > 0)
            hit = 1;
    }
    if (data->dda.side == 0)
        data->dda.wallDist = data->dda.sideDistX - data->dda.dx;
    else
        data->dda.wallDist = data->dda.sideDistY - data->dda.dy;
}
