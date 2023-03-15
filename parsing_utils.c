/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:28:31 by fabou-za          #+#    #+#             */
/*   Updated: 2023/03/02 23:44:57 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_mlx(t_data *mlx)
{
	char	*temp;
	int		j;

	j = 0;
	while (mlx->lines[j])
	{
		temp = mlx->lines[j];
		mlx->lines[j] = mlx->lines[j + 1];
		free(temp);
		j++;
	}
	free(mlx->lines);
	if (mlx->north_texture)
		free(mlx->north_texture);
	if (mlx->west_texture)
		free(mlx->west_texture);
	if (mlx->east_texture)
		free(mlx->east_texture);
	if (mlx->south_texture)
		free(mlx->south_texture);
}

void	clear_splited(char **s)
{
	char	*temp;
	int		j;

	j = 0;
	while (s[j])
	{
		temp = s[j];
		s[j] = s[j + 1];
		free(temp);
		j++;
	}
	free(s);
}

size_t	ft_maplen(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strlen2(char **s)
{
	size_t	i;

	i = 0;
	while ((*s)[i] && (*s)[i] != '\n')
		i++;
	(*s)[i] = '\0';
	return (i);
}

void	display_message_error(int if_error)
{
	if (if_error == -1)
		printf("Error\nParse error\n");
	else if (if_error == 3)
		printf("Error\nNo map found\n");
}
