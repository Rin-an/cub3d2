/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:18:54 by fabou-za          #+#    #+#             */
/*   Updated: 2023/03/01 16:03:49 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	mlx;
	int if_error;
	int fd;

	if (argc != 2)
		printf("Too many or few arguments!\n");
	else
	{
		if ((if_error = check_file_extension(argv[1], ".cub", &fd)) == 1)
			return (1);
		mlx.lines = NULL;
		init_mlx(&mlx);
		read_file(fd, &mlx);
		close(fd);
		if_error = parse_function(&mlx);
		display_message_error(if_error);
        if (if_error == -1 )//
        {
            free_mlx(&mlx);
			system("leaks cub3d");
          //  printf("byyyyyyyyyyyyyyyye\n");
            return (1);
        }
/*		int i = 0;
		printf("mlx map height is %d\n", mlx.map_height);
		while (mlx.map[i] && i <= mlx.map_height)
		{
			printf("string %d of map is '%s'\n", i, mlx.map[i]);
			i++;
		}*/
		printf("player position is [%d][%d]\n", (int)mlx.p.x, (int)mlx.p.y);
		printf("%c\n", mlx.map[(int)mlx.p.x][(int)mlx.p.y]);
        init_settings(&mlx);
        mlx_loop_hook(mlx.mlx_ptr, &draw, &mlx);
        hooks(&mlx);
        mlx_loop(mlx.mlx_ptr);
		free_mlx(&mlx);
		system("leaks cub3d");
	}
}
