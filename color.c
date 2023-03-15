/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:19:51 by fabou-za          #+#    #+#             */
/*   Updated: 2023/03/02 23:50:26 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	to_color(char **str)
{
	int	i;
	int	color;
	int	tmp;

	i = 0;
	color = 0;
	while (str[i])
	{
		tmp = ft_atoi(str[i]);
		if (tmp < 0 || tmp > 255)
			return (-1);
		color = color | (tmp << (16 - (i++ *8)));
	}
	return (color);
}

int	check_splited(char **s)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (s[i])
	{
		len = ft_strlen2(&s[i]);
		j = 0;
		while (s[i][j] == ' ' || s[i][j] == '\t')
			j++;
		while (s[i][len] == ' ' || s[i][len] == '\t')
			len--;
		while (s[i][j] && j < len)
		{
			if (ft_strchr("0123456789", s[i][j++]) == NULL)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	check_color(char **str)
{
	int	len;
	int	i;
	int	virgule;

	len = ft_strlen2(str);
	(*str)[len] = '\0';
	virgule = 0;
	i = 0;
	while ((*str)[i])
	{
		if (ft_strchr(" \t,0123456789", (*str)[i++]) == NULL)
			return (-1);
		if ((*str)[i] == ',')
			virgule++;
	}
	if (virgule != 2)
		return (-1);
	return (0);
}

int	color_stock(char c, char *str, t_data *mlx)
{
	char	**splited;
	int		color;
	char	*s;

	if (check_color(&str) == -1)
		return (-1);
	s = ft_strtrim(str, " \t");
	splited = ft_split(s, ',');
	free(s);
	if (!splited || ft_maplen(splited) != 3 || check_splited(splited) == -1)
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

int	parse_color(char **splited, char *str, bool *exist, t_data *mlx)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (str[i] == ' ')
		i++;
	if (!ft_strcmp(splited[0], "F") && !exist[5])
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
