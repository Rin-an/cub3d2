/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:28:31 by fabou-za          #+#    #+#             */
/*   Updated: 2023/02/25 19:09:36 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_map(char **map)
{
	char *temp;
	int j;

	j = 0;
	while (map[j])
	{
		temp = map[j];
		map[j] = map[j + 1];
		free(temp);
		j++;
	}
}

void	free_mlx(t_data *mlx)
{
	char *temp;
	int j;

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
	/*if (mlx->map)
		free_map(&mlx->map[0]);*/

}

void	clear_splited(char **s)
{
	char *temp;
	int j;

	j = 0;
	while(s[j])
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
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int ft_strlen2(char **s)
{
	size_t i;

	i = 0;
	while ((*s)[i] && (*s)[i] != '\n')
		i++;
	(*s)[i] = '\0';
	return (i);
}

/*int ft_strlenew2(char *s)
{
	size_t i;
	//char *str;

	i = 0;
    (*s) = ft_strtrim(*s, " \n");
	while ((*s)[i])
		i++;
	return (i);
}*/

int ft_strlenew(char **s)
{
	size_t i;

	i = 0;
    (*s) = ft_strtrim(*s, " \n");
	while ((*s)[i])
		i++;
	return (i);
}

void    display_message_error(int if_error)
{
	if (if_error == -1)
		printf("ERROR\nParse error\n");
	else if (if_error == 3)
		printf("ERROR\nNo map found\n");
}

