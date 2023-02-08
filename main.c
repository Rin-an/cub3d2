/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:59:44 by ssadiki           #+#    #+#             */
/*   Updated: 2023/02/08 19:22:05 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"

double	vec_dist(double x, double y)
{
	return (sqrt(x*x + y * y));
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

int	map[MAP_WIDTH][MAP_HEIGHT]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
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
	else if (keycode == 13)
	{
		printf("up motion: %i, %i\n",map[(int) (data->p.x + data->p.dirX * MOVE_SPEED)][(int) data->p.y], map[(int) data->p.x][(int) (data->p.y + data->p.dirY * MOVE_SPEED)]);
	
		if (map[(int) (data->p.x + data->p.dirX * MOVE_SPEED)][(int) data->p.y] == 0)
			data->p.x += data->p.dirX * MOVE_SPEED;
		if (map[(int) data->p.x][(int) (data->p.y + data->p.dirY * MOVE_SPEED)] == 0)
			data->p.y += data->p.dirY * MOVE_SPEED;
	}
	else if (keycode == 1)
	{
		printf("walk down : %i, %i\n",map[(int) (data->p.x - data->p.dirX * MOVE_SPEED)][(int) data->p.y], map[(int) data->p.x][(int) (data->p.y - data->p.dirY * MOVE_SPEED)]);
		if (map[(int) (data->p.x - data->p.dirX * MOVE_SPEED)][(int) data->p.y] == 0)
			data->p.x -= data->p.dirX * MOVE_SPEED;
		if (map[(int) data->p.x][(int) (data->p.y - data->p.dirY * MOVE_SPEED)] == 0)
			data->p.y -= data->p.dirY * MOVE_SPEED;
	}
	else if (keycode == 123)
	{
		double	tmpdir = data->p.dirX;
		double	tmpplane = data->vec.planeX;
		data->p.dirX = tmpdir * cos(ROTATION_SPEED) - data->p.dirY * sin(ROTATION_SPEED);
		data->p.dirY = tmpdir * sin(ROTATION_SPEED) + data->p.dirY * cos(ROTATION_SPEED);
		data->vec.planeX = tmpplane * cos(ROTATION_SPEED) - data->vec.planeY * sin(ROTATION_SPEED);
		data->vec.planeY = tmpplane * sin(ROTATION_SPEED) + data->vec.planeY * cos(ROTATION_SPEED);
	}
	else if (keycode == 124)
	{
		double	tmpdir = data->p.dirX;
		double	tmpplane = data->vec.planeX;
		data->p.dirX = tmpdir * cos(-ROTATION_SPEED) - data->p.dirY * sin(-ROTATION_SPEED);
		data->p.dirY = tmpdir * sin(-ROTATION_SPEED) + data->p.dirY * cos(-ROTATION_SPEED);
		data->vec.planeX = tmpplane * cos(-ROTATION_SPEED) - data->vec.planeY * sin(-ROTATION_SPEED);
		data->vec.planeY = tmpplane * sin(-ROTATION_SPEED) + data->vec.planeY * cos(-ROTATION_SPEED);
	}
	/*else if (keycode == 2)
	{
		data->p.x += -cos(data->p.rotation_angle) * MOVE_SPEED;
		data->p.y += (sin(data->p.rotation_angle) * MOVE_SPEED);
	//	data->p.x += MOVE_SPEED;
	}
	else if (keycode == 0)
	{
		data->p.x += -(cos(data->p.rotation_angle) * MOVE_SPEED);
		data->p.y += sin(data->p.rotation_angle) * MOVE_SPEED;
	//	data->p.x -= MOVE_SPEED;
	}*/
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
void	**load_textures(t_data *data)
{
	void	**textures;
	int		img_width;
	int		img_height;

	textures = malloc(sizeof(void *) * 4);
	if (!textures)
		return (NULL);
	textures[0] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/eagle.xpm", &img_width, &img_height);
	textures[1] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/purplestone.xpm", &img_width, &img_height);
	textures[2] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/redbrick.xpm", &img_width, &img_height);
	textures[3] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/colorstone.xpm", &img_width, &img_height);
	return (textures);
}

int	get_color(int x, int y)
{
	if (map[x][y] == 1)
		return (0x222222);
	if (map[x][y] == 2)
		return (0xFF0000);
	if (map[x][y] == 3)
		return (0xFFFF00);
	if (map[x][y] == 4)
		return (0x0000FF);
	if (map[x][y] == 5)
		return (0);
	else
		return (0xFFFFFF);
}

/*void    render_map(t_data *data)
{
    for(int i = 0; i < MAP_WIDTH; i++)
    {
        for(int j = 0; j < MAP_HEIGHT; j++)
        {
            int color = get_color(i, j);
            for (int i2 = i * TILE_SIZE; i2 < (i * TILE_SIZE) + TILE_SIZE; i2++)
            {
                for (int j2 = j * TILE_SIZE; j2 < (j * TILE_SIZE) + TILE_SIZE ; j2++)
                    img_pix_put(&(data->img), j2, i2, color);
            }
        }
    }
}*/

void	render_map(t_data *data, double wallDist, int x)
{
	int	wall_height;
	int	wall_start;
	int	wall_end;
	int	color;

	wall_height = (int) (WIN_HEIGHT / wallDist);
	wall_start = -wall_height / 2 + WIN_HEIGHT / 2;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = wall_height / 2 + WIN_HEIGHT / 2;
	if (wall_end >= WIN_HEIGHT)
		wall_end = WIN_HEIGHT - 1;
	if (map[data->vec.mapX][data->vec.mapY] == 1)
		color = 0xFF0000;
	else if (map[data->vec.mapX][data->vec.mapY] == 2)
		color = 0x00FF00;
	else if (map[data->vec.mapX][data->vec.mapY] == 3)
		color = 0x0000FF;
	else if (map[data->vec.mapX][data->vec.mapY] == 4)
		color = 0xFFFFFF;
	else
		color = 0x000000;
	if (data->p.side == 1)
		color /= 2;
	for (int y = wall_start; y < wall_end; y++)
		img_pix_put(&data->img, x, y, color);
}

double	dda(t_data *data, double rayX, double rayY)
{
	int		stepX;
	int		stepY;
	int		hit;
	double	perpWallDist;

	hit = 0;
	data->vec.mapX = (int) data->p.x;
	data->vec.mapY = (int) data->p.y;
	if (rayX == 0)
		data->vec.deltaDistX = 1e30;
	else
		data->vec.deltaDistX = fabs(1 / rayX);
	if (rayY == 0)
		data->vec.deltaDistY = 1e30;
	else
		data->vec.deltaDistY = fabs(1 / rayY);
	if (rayX < 0)
	{
		stepX = -1;
		data->vec.sideDistX = (data->p.x - data->vec.mapX ) * data->vec.deltaDistX;
	}
	else
	{
		stepX = 1;
		data->vec.sideDistX = (data->vec.mapX + vec_dist(data->p.dirX, data->p.dirY) - data->p.x) * data->vec.deltaDistX;
	}
	if (rayY < 0)
	{
		stepY = -1;
		data->vec.sideDistY = (data->p.y - data->vec.mapY ) * data->vec.deltaDistY;
	}
	else
	{
		stepY = 1;
		data->vec.sideDistY = (data->vec.mapY + vec_dist(data->p.dirX, data->p.dirY) - data->p.y) * data->vec.deltaDistY;
	}
	while (!hit)
	{
		if (data->vec.sideDistX < data->vec.sideDistY)
		{
			data->p.side = 0;
			data->vec.sideDistX += data->vec.deltaDistX;
			data->vec.mapX += stepX;
		}
		else
		{
			data->p.side = 1;
			data->vec.sideDistY += data->vec.deltaDistY;
			data->vec.mapY += stepY;
		}
		if (map[data->vec.mapX][data->vec.mapY] > 0)
			hit = 1;
	}
	if (data->p.side == 0)
		perpWallDist = data->vec.sideDistX - data->vec.deltaDistX;
	else
		perpWallDist = data->vec.sideDistY - data->vec.deltaDistY;
	return (perpWallDist);
}

int	draw(t_data *data)
{
	void	**textures;

	if (!data->win_ptr)
		return (1);
	//render_map(data);
	textures = load_textures(data);
	for (int x = 0; x < WIN_WIDTH; x++)
	{
		double	cameraX = 2 * x / (double)WIN_WIDTH - 1;
		double	rayX = data->p.dirX + data->vec.planeX * cameraX;
		double	rayY = data->p.dirY + data->vec.planeY * cameraX;
	//	printf("%.1f, %.f, %.f\n", cameraX, rayX, rayY);
		render_map(data, dda(data, rayX, rayY), x);	
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	return (0);
}

void	have_fun(t_data *data)
{
	data->p.x = 22;
	data->p.y = 12;
	data->p.dirX = -1;
	data->p.dirY = 0;
	data->vec.planeX = 0;
	data->vec.planeY = 0.66;
	mlx_loop_hook(data->mlx_ptr, &draw, data);
}


int	main(int argc, char **argv)
{
	t_data	data;

	(void)argv;
	if (argc != 2)
		printf("Too many or few arguments!\n");
	else
	{
		init_mlx(&data);
		have_fun(&data);
		hooks(&data);
		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
		free(data.mlx_ptr);
	}
	return (0);
}
