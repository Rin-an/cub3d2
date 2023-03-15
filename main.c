/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:18:54 by fabou-za          #+#    #+#             */
/*   Updated: 2023/03/03 03:12:58 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	have_fun(t_data *mlx)
{
	mlx_loop_hook(mlx->mlx_ptr, &draw, mlx);
	hooks(mlx);
	mlx_loop(mlx->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_data	mlx;
	int		if_error;
	int		fd;

	if (argc != 2)
		printf("Too many or few arguments!\n");
	else
	{
		if_error = check_file_extension(argv[1], ".cub", &fd);
		if (if_error == 1)
			return (1);
		init_mlx(&mlx);
		read_file(fd, &mlx);
		close(fd);
		if_error = parse_function(&mlx);
		display_message_error(if_error);
		if (if_error == -1)
			return (free_mlx(&mlx), 1);
		init_mlx2(&mlx);
		init_settings(&mlx);
		have_fun(&mlx);
		free_mlx(&mlx);
	}
	return (0);
}
