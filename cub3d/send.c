/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:59:44 by ssadiki           #+#    #+#             */
/*   Updated: 2023/01/28 19:20:43 by ssadiki          ###   ########.fr       */
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
	{
		data->p.walkDirection = 1;
	}
	else if (keycode == 1 || keycode == 125)
	{
		data->p.walkDirection = -1;
	}
	else if (keycode == 0 || keycode == 123)
	{
		data->p.turnDirection = 1;
		data->p.rotation_angle += data->p.turnDirection * ROTATION_SPEED;
	}
	else if (keycode == 2 || keycode == 124)
	{
		data->p.turnDirection = -1;
		data->p.rotation_angle += data->p.turnDirection * ROTATION_SPEED;
	}
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

void	render_grid(t_data *data)
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

int	is_wall(int x, int y)
{
	int	gridindex_x;
	int	gridindex_y;
	
	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return (1);
	gridindex_x = x / 32;
	gridindex_y = y / 32;
	if (grid[gridindex_y][gridindex_x] == 1)
		return (1);
	return (0);
}

void	update_player(t_data *data)
{
	int	move_step;
	int	new_x;
	int	new_y;

	move_step = data->p.walkDirection * MOVE_SPEED;
	new_x = data->p.x + cos(data->p.rotation_angle) * move_step;
	new_y = data->p.y + sin(data->p.rotation_angle) * move_step;
	if (!is_wall(new_x, new_y))
	{
		data->p.x = new_x;
		data->p.y = new_y;
	}
}

/*int	render_player(t_data *data)
{
	img_pix_put(&data->img, data->p.x, data->p.y, 0xFF0000);
	float	currentx = data->p.x;
	float	currenty = data->p.y;
	float	x1;
	float	y1;
	float	dx;
	float	dy;
	float	side_length;
	float	x_inc;
	float	y_inc;
	double	ray_angle = data->p.rotation_angle - (FOV / 2);

	//for (int i = 0; i < NUM_RAYS; i++)
	//{
		x1 = data->p.x + cos(ray_angle) * 20;
		y1 = data->p.y + sin(ray_angle) * 20;
		dx = x1 - data->p.x;
		dy = y1 - data->p.y;
		if (fabsf(dx) >= fabsf(dy))
			side_length = fabsf(dx);
		else
			side_length = fabsf(dy);
		x_inc = dx / side_length;
		y_inc = dy / side_length;
		currentx = data->p.x;
		currenty = data->p.y;
		for (int j = 0; j <= side_length; j++)
		{
			img_pix_put(&data->img, roundf(currentx), roundf(currenty), 0xFF0000);
			currentx += x_inc;
			currenty += y_inc;
		}
	//	ray_angle += FOV / NUM_RAYS;
	//}
	return (0);
}*/

int	render_player(t_data *data)
{
	img_pix_put(&data->img, data->p.x, data->p.y, 0xFF0000);
	double	ray_angle = data->p.rotation_angle - (FOV / 2);
	int	x0 = data->p.x;
	int	y0 = data->p.y;
	int	x1 = data->p.x + cos(ray_angle) * 20;
	int	y1 = data->p.y + sin(ray_angle) * 20;
   	int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (1) 
	{
        img_pix_put(&data->img, x0, y0, 0xFF0000);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
	return (0);
}
int	draw(t_data *data)
{
	if (!data->win_ptr)
		return (1);
	update_player(data);
	render_grid(data);
	render_player(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	return (0);
}

void	have_fun(t_data *data)
{
	data->p.x = WIN_WIDTH / 2;
	data->p.y = WIN_HEIGHT / 2;
	data->p.walkDirection = 0;
	data->p.turnDirection = 0;
	data->p.rotation_angle = M_PI / 2;
	mlx_loop_hook(data->mlx_ptr, &draw, data);
}


int	main(int argc, char **argv)
{
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
