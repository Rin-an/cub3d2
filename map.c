/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:56:31 by fabou-za          #+#    #+#             */
/*   Updated: 2023/03/02 22:56:33 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_suite(char **str, t_info info, int *player_existence, t_data *mlx)
{
	int		i;
	t_point	point;
	int		j;

	i = 1;
	j = info.j;
	while (str[j][i] && i < info.len - 1)
	{
		if (ft_strchr("NSWE01 ", str[j][i]) == NULL)
			return (1);
		point.j = j;
		point.i = i;
		if (player_check(str[j][i], player_existence, mlx, point) == 1)
			return (1);
		if (str[j][i] != '1' && str[j][i] != ' ')
		{
			ft_strlen2(&str[j + 1]);
			if (!str[j + 1][i] || !str[j - 1][i] || str[j][i - 1] == ' ' \
					|| str[j][i + 1] == ' '
					|| str[j - 1][i] == ' ' || str[j + 1][i] == ' ')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_first_last_maplines(int len_first, int len_map, char **str)
{
	int	j;
	int	len_last;

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

int	check_borders(char **s, int *len_first)
{
	int		i;
	char	*str;
	int		len;

	(*len_first) = ft_strlen2(s);
	str = *s;
	i = 0;
	len = (*len_first) - 1;
	while (str[i] == ' ')
		i++;
	while (str[len] == ' ')
		len --;
	if (str[i] != '1' || str[len] != '1')
		return (1);
	return (0);
}

void	ft_check_map_end(char **str, t_data *mlx)
{
	int	i;
	int	j;
	int	len_map;

	len_map = ft_maplen(str);
	i = len_map;
	while (str[i - 1])
	{
		j = 0;
		while (str[i - 1][j] == ' ')
			j++;
		if (ft_strcmp(&str[i - 1][j], "\n") == 0)
			len_map--;
		else
			break ;
		i--;
	}
	mlx->map_height = len_map - 1;
}

int	check_map(char **str, t_data *mlx)
{
	int		len_first;
	int		j;
	int		player_existence;
	t_info	info;

	player_existence = 0;
	len_first = ft_strlen2(&str[0]);
	ft_check_map_end(str, mlx);
	if (check_first_last_maplines(len_first, mlx->map_height + 1, str) == 1)
		return (1);
	j = 1;
	while (str[j] && (j <= mlx->map_height))
	{
		if (check_borders(&str[j], &len_first) == 1)
			return (1);
		info.len = len_first;
		info.j = j;
		if (check_map_suite(&str[0], info, &player_existence, mlx) == 1)
			return (1);
		j++;
	}
	if (player_existence != 1)
		return (1);
	return (0);
}
