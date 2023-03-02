/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:19:51 by fabou-za          #+#    #+#             */
/*   Updated: 2023/02/28 15:06:20 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int to_color(char **str)
{
	int i;
	int color;
	int tmp;

	i = 0;
	color = 0;
	while(str[i])
	{
		tmp = ft_atoi(str[i]);
		printf("the number %d\n", tmp);//
		if (tmp < 0 || tmp > 255)
			return (-1);
		color = color | (tmp << (16 - (i++ * 8)));
	}
	return (color);
}

int check_color(char **str)
{
	int len;
	int i;

	len = ft_strlen2(str);
	(*str)[len] = '\0';
	i = 0;
	while ((*str)[i])
	{
		if (ft_strchr(" \t,0123456789", (*str)[i++]) == NULL)
			return (-1);
	}
	//printf("finish herei with str '%s' \n", *str);
	return (0);
}

int color_stock(char c, char *str, t_data *mlx)
{
	char **splited;
	int color;
	char *s;

	if (check_color(&str) == -1)
		return (-1);
	s = ft_strtrim(str, " \t");
	//printf("now we're here\n");
	splited = ft_split(s, ',');
	free(s);
	if (!splited ||ft_maplen(splited) != 3)
	{
		clear_splited(splited);
		return (-1);
	}
	color = to_color(&splited[0]);
	clear_splited(splited);
	if (color == -1)
		return (-1);
	if (c == 'F')
		mlx->floor_color = color;
	else
		mlx->ceiling_color = color;
	return (0);
}

int parse_color(char **splited, char *str, bool *exist, t_data *mlx)
{
	int i;
	int status;

	i = 0;
	status = 0;
	//printf("string color is '%s'\n", str);
	while (str[i] == ' ')
		i++;
	if (!strcmp(splited[0], "F") && !exist[5])
	{
		exist[5] = 1;
		if (str[i] && str[i] == 'F')
			i++;
		status = color_stock('F', &str[i], mlx);
	}
	else if (!exist[4])
	{
		exist[4] = 1;
		if (str[i] && str[i] == 'C')
			i++;
		status = color_stock('C', &str[i], mlx);
	}
	else
		return (-1);
	return (status);
}
