/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:56:31 by fabou-za          #+#    #+#             */
/*   Updated: 2023/03/01 02:14:59 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_map_suite(char **str, int len_first, int j, int *player_existence, t_data *mlx)
{
    int i;

    i = 1;
	while (str[j][i] && i < len_first - 1)
	{
		if (ft_strchr("NSWE01 ", str[j][i]) == NULL)
			return (1);
		if (ft_strchr("NSWE", str[j][i]) != NULL)
		{
			if (*player_existence == 1)
				return (1);
			else
			{
				(*player_existence) = 1;
				mlx->p.x = j;
				mlx->p.y = i;
			}
		}
		if (str[j][i] != '1' && str[j][i] != ' ')
        {
			ft_strlen2(&str[j + 1]);
			if (!str[j + 1][i] || !str[j - 1][i] || str[j][i - 1] == ' ' || str[j][i + 1] == ' ' \
					|| str[j - 1][i] == ' ' || str[j + 1][i] == ' ')
					return (1);
         }
        i++;
	}
	return (0);
}

int check_first_last_maplines(int len_first, int len_map, char **str)
{
	int j;
    int len_last;

    len_last = ft_strlen2(&str[len_map - 1]);
	j = 0;
	while ((str[0][j] && j <= len_first - 1))
	{
		if ((str[0][j] != '1' && str[0][j] != ' '))
			return (1);
		j++;
	}
	j = 0;
	while (str[len_map - 1][j] && j <= len_last - 1)
	{
		if (str[len_map - 1][j] != '1' && str[len_map - 1][j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

int check_borders(char *str, int len)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[len] == ' ')
		len --;
	if (str[i]!= '1' || str[len] != '1')
		return (1);
	return (0);
}

void	ft_check_map_end(char **str, int *len_map)
{
	int i;
	int j;
	//char *str;

	i = (*len_map);
	//str = ft_strtrim();
	while (str[i - 1])
	{
		j = 0;
		while (str[i - 1][j] == ' ')
			j++;
		//printf("seg lteht string is '%s' and char is '%c'\n", str[i - 1], str[i - 1][j]);
		if (ft_strcmp(&str[i - 1][j], "\n") == 0)
			(*len_map)--;
		else
			break;
		//printf("seg above\n");
		i--;
	}
	//printf("finish\n");
	/*while (ft_strcmp(&str[i - 1][j], "\n") == 0)
	{
		i--;
		*len_map = i;
	}*/
}

int check_map(char **str, t_data *mlx)
{
	int len_first;
	int len_map;
	int j;
	int player_existence;
	
	player_existence = 0;
	len_first = ft_strlen2(&str[0]);
	len_map = ft_maplen(str);

	//printf("map len is %d\n and last string is '%s'\n", len_map, str[len_map - 1]);
	ft_check_map_end(str, &len_map);
	printf("map len after check is %d\n and last string is '%s'\n", len_map, str[len_map - 1]);
	mlx->map_height = len_map - 1;
	printf("map len after check is %d\n and last string is '%s'\n", len_map, str[mlx->map_height]);
	if ((check_first_last_maplines(len_first, len_map, str) == 1)\
		   	|| len_map <= 2)
		return (1);
	j = 1;
	while (str[j] && (j <= len_map - 1))
	{
		len_first = ft_strlen2(&str[j]);
		if (check_borders(str[j], len_first - 1) == 1)
			return (1);
		if (check_map_suite(&str[0], len_first, j, &player_existence, mlx) == 1)
			return (1);
		j++;
	}
	if (player_existence != 1)
		return (1);
	return (0);
}
