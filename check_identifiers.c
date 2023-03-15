/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:02:13 by fabou-za          #+#    #+#             */
/*   Updated: 2023/03/02 23:50:53 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_textures(char *texture, char identif, t_data *mlx)
{
	int	len;
	int	fd;

	if (texture == NULL)
		return (-1);
	len = ft_strlen2(&texture);
	if (check_file_extension(texture, ".xpm", &fd) == 1)
		return (-1);
	close(fd);
	if (identif == 'N')
		mlx->north_texture = strdup(texture);
	else if (identif == 'S')
		mlx->south_texture = strdup(texture);
	else if (identif == 'E')
		mlx->east_texture = strdup(texture);
	else if (identif == 'W')
		mlx->west_texture = strdup(texture);
	return (0);
}

int	fill_identif(bool *exist, char *str, t_data *mlx, char c)
{
	int	status;

	status = 0;
	(*exist) = 1;
	status = read_textures(str, c, mlx);
	return (status);
}

int	check_identifiers(char **str, bool *exist, t_data *mlx)
{
	int	status;
	int	len;

	status = 0;
	len = 0;
	while (str[len])
		len++;
	if (str[2] && ft_strcmp(str[2], "\n") != 0)
		return (-1);
	if (!ft_strcmp("NO", str[0]) && !exist[0])
		status = fill_identif(&exist[0], str[1], mlx, 'N');
	else if (!ft_strcmp("SO", str[0]) && !exist[1])
		status = fill_identif(&exist[1], str[1], mlx, 'S');
	else if (!ft_strcmp("EA", str[0]) && !exist[2])
		status = fill_identif(&exist[2], str[1], mlx, 'E');
	else if (!ft_strcmp("WE", str[0]) && !exist[3])
		status = fill_identif(&exist[3], str[1], mlx, 'W');
	else
		return (-1);
	if (status == -1)
		return (-1);
	return (0);
}

int	check_fun(char *line, bool *exist, t_data *mlx)
{
	int		if_error;
	char	**splited;

	if_error = 0;
	splited = ft_split(line, ' ');
	if (!ft_strcmp(splited[0], "F") || !ft_strcmp(splited[0], "C"))
		if_error = parse_color(splited, line, exist, mlx);
	else if (splited[0][0] == '1' || splited[0][0] == '0')
		if_error = 2;
	else if (!ft_strcmp("\n", splited[0]))
		if_error = 0;
	else
		if_error = check_identifiers(splited, exist, mlx);
	clear_splited(splited);
	if (if_error == -1)
		free(exist);
	return (if_error);
}

int	check_function(char **lines, int *j, bool *exist, t_data *mlx)
{
	int	if_error;

	if_error = 0;
	while (lines[*j])
	{
		if_error = check_fun(lines[*j], &exist[0], mlx);
		if (if_error == 2)
			break ;
		if (if_error == -1)
			return (-1);
		(*j)++;
	}
	return (if_error);
}
