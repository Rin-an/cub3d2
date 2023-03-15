/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:37:26 by fabou-za          #+#    #+#             */
/*   Updated: 2023/03/02 23:53:04 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_dup(bool *exist)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (exist[i++] == 0)
		{
			free(exist);
			return (-1);
		}
	}
	return (0);
}

int	parse_function(t_data *mlx)
{
	int		j;
	int		if_error;
	bool	*exist;
	int		if_dup;

	exist = ft_calloc(6, 1);
	if_dup = 0;
	j = 0;
	if_error = check_function(mlx->lines, &j, &exist[0], mlx);
	if (if_error == -1)
		return (-1);
	if_dup = check_dup(&exist[0]);
	if (if_dup == -1)
		return (-1);
	free(exist);
	if (if_error == 2)
	{
		if (check_map(&mlx->lines[j], mlx) == 1)
			return (-1);
		mlx->map = &mlx->lines[j];
	}
	else
		return (3);
	return (0);
}

void	fill_lines(t_data *mlx, char *s, char **temp)
{
	int	j;

	j = 0;
	if (temp)
	{
		while (temp[j])
		{
			mlx->lines[j] = temp[j];
			j++;
		}
	}
	mlx->lines[j++] = s;
	mlx->lines[j] = 0;
}

void	read_file(int fd, t_data *mlx)
{
	char	*s;
	char	**temp;
	int		i;

	i = 1;
	temp = NULL;
	s = get_next_line(fd);
	while (s)
	{
		temp = mlx->lines;
		mlx->lines = malloc((i + 1) * sizeof(char *));
		if (!mlx->lines)
		{
			free_mlx(mlx);
			exit(1);
		}
		fill_lines(mlx, s, temp);
		free(temp);
		i++;
		s = get_next_line(fd);
	}
}

int	check_file_extension(char *s, char *extension, int *fd)
{
	char	*pt;

	pt = NULL;
	if (ft_strrchr(s, '.') == ft_strrchr(s, '.'))
	{
		pt = ft_strrchr(s, '.');
		if (!pt || ft_strcmp(pt, extension))
			return (1);
	}
	else if (ft_strrchr(s, '.') != ft_strrchr(s, '.'))
		return (1);
	(*fd) = open(s, O_RDONLY);
	if (*fd < 0)
		return (1);
	return (0);
}
