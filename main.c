/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:59:44 by ssadiki           #+#    #+#             */
/*   Updated: 2023/01/09 21:22:35 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"

//Check for duplicates
bool	check_identifiers(char **s, bool *exist, void *tex)
{
	(void)tex;
	if (!ft_strcmp(s[0], "NO\n") && !exist[0])
		exist[0] = 1;
	else if (!ft_strcmp(s[0], "SO\n") && !exist[1])
		exist[1] = 1;
	else if (!ft_strcmp(s[0], "WE\n") && !exist[2])
		exist[2] = 1;
	else if (!ft_strcmp(s[0], "EA\n") && !exist[3])
		exist[3] = 1;
	else if (!ft_strcmp(s[0], "F\n") && !exist[4])
		exist[4] = 1;
	else if (!ft_strcmp(s[0], "C\n") && !exist[5])
		exist[5] = 1;
	else if (ft_strcmp(s[0], "\n"))
		return (true);
	return (false);
}

void	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit(EXIT_FAILURE);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!data->win_ptr)
		exit(EXIT_FAILURE);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
	pixel = img->addr + (img->line_len * y + x * (img->bpp / 8));
	*(int *)pixel = color;
}

//FOR THE SAKE OF MY SANITY

/*
 * HOOKS
 */

void	exit_keypress(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(EXIT_SUCCESS);
}

int		exit_button(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(EXIT_SUCCESS);
}

int	keypress(int keycode, t_data *data)
{
	if (keycode == 53)
		exit_keypress(data);
	else if (keycode == 13 || keycode == 126)
		data->p.walkDirection = 1;
	else if (keycode == 1 || keycode == 125)
		data->p.walkDirection = -1;
	else if (keycode == 2 || keycode == 124)
		data->p.turnDirection = 1;
	else if (keycode == 0 || keycode == 123)
		data->p.turnDirection = -1;
	return (0);
}

int	keyrelease(int keycode, t_data *data)
{
	if (keycode == 53)
		exit_keypress(data);
	else if (keycode == 13 || keycode == 126)
		data->p.walkDirection = 0;
	else if (keycode == 1 || keycode == 125)
		data->p.walkDirection = 0;
	else if (keycode == 2 || keycode == 124)
		data->p.turnDirection = 0;
	else if (keycode == 0 || keycode == 123)
		data->p.turnDirection = 0;
	return (0);
}

void	hooks(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 0, &keypress, data);
	mlx_hook(data->win_ptr, 3, 0, &keyrelease, data);
	mlx_hook(data->win_ptr, 17, 0, &exit_button, data);
	mlx_loop(data->mlx_ptr);
}
//END OF HOOKS

void	render_grid(t_data *data, int grid[11][15])
{
	for(int i = 0; i < 11; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			int	color = (grid[i][j] == 1 ? 0x222222 : 0xFFFFFF);
			for (int i2 = i * TILE_SIZE; i2 < (i * TILE_SIZE) + TILE_SIZE; i2++)
			{
				for (int j2 = j * TILE_SIZE; j2 < (j * TILE_SIZE) + TILE_SIZE ; j2++)
					img_pix_put(&(data->img), j2, i2, color);
			}
		}

	}
}

void	update_player(t_data *data)
{
	data->p.rotation_angle += data->p.turnDirection * ROTATION_SPEED;
}

int	render_player(t_data *data)
{
	update_player(data);
	img_pix_put(&data->img, data->p.x, data->p.y, 0xFF0000);
	printf("%i\n", data->p.turnDirection);
	for (double i = data->p.y; i < data->p.y + sin(data->p.rotation_angle) * 20; i++)
	{
		for (double j = data->p.x; j < data->p.x + cos(data->p.rotation_angle) * 20; j++)
		{
			img_pix_put(&data->img, j, i, 0xFF0000);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

void	have_fun(t_data *data)
{
	int grid[11][15] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

	render_grid(data, grid);
	data->p.x = WIN_WIDTH / 2;
	data->p.y = WIN_HEIGHT / 2;
	data->p.walkDirection = 0;
	data->p.turnDirection = 0;
	data->p.rotation_angle = M_PI / 2;
	mlx_loop_hook(data->mlx_ptr, &render_player, data);;
}


int	main(int argc, char **argv)
{
	//	int		i;
	char	*s;
	t_data	data;

	if (argc != 2)
		printf("Too many or few arguments!\n");
	else
	{
		if (ft_strchr(argv[1], '.') == ft_strrchr(argv[1], '.'))
		{
			char	*pt = ft_strchr(argv[1], '.');

			if (!pt || ft_strcmp(pt, ".cub"))
				return (printf("Error\nWrong extension!"));
		}
		else
			return (printf("Error\nWrong extension!"));
		int	fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (printf("Error\nCannot open the file!"));
		char	**sp;
		//CHECK IF INDENTIFIER EXIST
		bool	*exist = ft_calloc(sizeof(bool), 6);
		//TEXUTRES ARRAY
		void	*textures = malloc(sizeof(void) * 6);
		if (!textures)
			return (printf("Error\nMalloc failed!\n"));
		init_mlx(&data);
		s = get_next_line(fd);
		while (s)
		{
			sp = ft_split(s, ' ');
			if (!sp)
				return (printf("Error\nSomething went wrong in split!"));
			if (check_identifiers(sp, exist, textures) == true)
				return (printf("Error\nWrong or duplicated identifiers!\n"));	
			free(s);
			s = get_next_line(fd);
		}
		have_fun(&data);
		hooks(&data);
		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
		free(data.mlx_ptr);
	}
	return (0);
}
