/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:59:44 by ssadiki           #+#    #+#             */
/*   Updated: 2023/02/25 23:54:11 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"

double  vec_dist(double x, double y)
{
	return (sqrt(x*x + y * y));
}

void    init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit(EXIT_FAILURE);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!data->win_ptr)
		exit(EXIT_FAILURE);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = (int *)mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	data->tex.textures = malloc(sizeof(int *) * 4);
	if (!data->tex.textures)
		exit(EXIT_FAILURE);
}

/*void    img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;

	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
	pixel = img->addr + (img->line_len * y + x * (img->bpp / 8));
	*(int *)pixel = color;
}*/

/* W = 87
 * E = 69
 * N = 78
 * S = 83
 */
int map[MAP_WIDTH][MAP_HEIGHT]=
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
	{1,4,4,4,4,4,4,4,4,0,0,0,'E',0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

//FOR THE SAKE OF MY SANITY

/*
 * HOOKS
 */

void    exit_keypress(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(EXIT_SUCCESS);
}

int     exit_button(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(EXIT_SUCCESS);
}

int keypress(int keycode, t_data *data)
{
	if (keycode == 53)
		exit_keypress(data);
	else if (keycode == 13) //up move
	{
		if (map[(int) (data->p.x + data->p.dirX* data->p.move_speed)][(int) data->p.y] == 0)
			data->p.x += data->p.dirX * data->p.move_speed;
		if (map[(int) data->p.x][(int) (data->p.y + data->p.dirY * data->p.move_speed)] == 0)
			data->p.y += data->p.dirY * data->p.move_speed;
	}
	else if (keycode == 1) // down move
	{
		if (map[(int) (data->p.x - data->p.dirX * data->p.move_speed)][(int) data->p.y] == 0)
			data->p.x -= data->p.dirX * data->p.move_speed;
		if (map[(int) data->p.x][(int) (data->p.y - data->p.dirY * data->p.move_speed)] == 0)
			data->p.y -= data->p.dirY * data->p.move_speed;
	}
	else if (keycode == 0) //left move
	{
		if (map[(int) (data->p.x - data->vec.planeX * data->p.move_speed)][(int) data->p.y] == 0)
			data->p.x -= data->vec.planeX * data->p.move_speed * data->p.direction;
		if (map[(int) data->p.x][(int) (data->p.y - data->vec.planeY * data->p.move_speed)] == 0)
			data->p.y -= data->vec.planeY * data->p.move_speed * data->p.direction;
	}
	else if (keycode == 2) // right move
	{
		if (map[(int) (data->p.x + data->vec.planeX * data->p.move_speed)][(int) data->p.y] == 0)
			data->p.x += data->vec.planeX * data->p.move_speed * data->p.direction;
		if (map[(int) data->p.x][(int) (data->p.y + data->vec.planeY * data->p.move_speed)] == 0)
			data->p.y += data->vec.planeY * data->p.move_speed * data->p.direction;
	}
	else if (keycode == 123)
	{
		double  tmpdir = data->p.dirX;
		double  tmpplane = data->vec.planeX;
		data->p.dirX = data->p.dirX * cos(data->p.rotation_speed) - data->p.dirY * sin(data->p.rotation_speed);
		data->p.dirY = tmpdir * sin(data->p.rotation_speed) + data->p.dirY * cos(data->p.rotation_speed);
		data->vec.planeX = data->vec.planeX * cos(data->p.rotation_speed) - data->vec.planeY * sin(data->p.rotation_speed);
		data->vec.planeY = tmpplane * sin(data->p.rotation_speed) + data->vec.planeY * cos(data->p.rotation_speed);
	}
	else if (keycode == 124)
	{
		double  tmpdir = data->p.dirX;
		double  tmpplane = data->vec.planeX;
		data->p.dirX = data->p.dirX * cos(-data->p.rotation_speed) - data->p.dirY * sin(-data->p.rotation_speed);
		data->p.dirY = tmpdir * sin(-data->p.rotation_speed) + data->p.dirY * cos(-data->p.rotation_speed);
		data->vec.planeX = data->vec.planeX * cos(-data->p.rotation_speed) - data->vec.planeY * sin(-data->p.rotation_speed);
		data->vec.planeY = tmpplane * sin(-data->p.rotation_speed) + data->vec.planeY * cos(-data->p.rotation_speed);
	}
	else if (keycode == 15)
	{
		data->p.x = 22;
		data->p.y = 12;
		data->p.dirX = -1;
		data->p.dirY = 0;
		data->vec.planeY = tan(FOV);
		data->vec.planeX = 0;
		data->p.direction = 1;
	}
	return (0);
}

void    hooks(t_data *data)
{   mlx_hook(data->win_ptr, 2, 0, &keypress, data);
	mlx_hook(data->win_ptr, 17, 0, &exit_button, data);
	mlx_loop(data->mlx_ptr);
}
//END OF HOOKS

void    load_textures(t_data *data)
{
	data->tex.img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/eagle.xpm", &data->tex.tex_width, &data->tex.tex_height);
	//data->tex.textures[1] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/purplestone.xpm", &data->tex.tex_width, &data->tex.tex_height);
	//data->tex.textures[2] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/redbrick.xpm", &data->tex.tex_width, &data->tex.tex_height);
	//data->tex.textures[3] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/colorstone.xpm", &data->tex.tex_width, &data->tex.tex_height);
	//data->tex.textures[4] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/barrel.xpm", &data->tex.tex_width, &data->tex.tex_height);
//	printf("img_width = %i, img_height = %i\n", img_width, img_height);
	data->tex.img.addr = (int *)mlx_get_data_addr(data->tex.img.mlx_img, &data->tex.img.line_len, &data->tex.img.bpp, &data->tex.img.endian);
}

/*int get_color(int x, int y)
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
	return (0xFFFFFF);
	if (map[x][y] != 0)
		load_textures(data);
}*/

/*void    render_mini_map(t_data *data)
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

/*void    render_map(t_data *data, int x)
{
	int wall_height;
	int wall_start;
	int wall_end;
	int color;

	if (data->dda.wallDist == 0)
		data->dda.wallDist++;
	wall_height = (int) (WIN_HEIGHT / data->dda.wallDist);
	wall_start = -wall_height / 2 + WIN_HEIGHT / 2;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = wall_height / 2 + WIN_HEIGHT / 2;
	if (wall_end >= WIN_HEIGHT)
		wall_end = WIN_HEIGHT - 1;
	if (map[data->dda.mapX][data->dda.mapY] == 1)
		color = 0xFF0000;
	else if (map[data->dda.mapX][data->dda.mapY] == 2)
		color = 0x00FF00;
	else if (map[data->dda.mapX][data->dda.mapY] == 3)
		color = 0x0000FF;
	else if (map[data->dda.mapX][data->dda.mapY] == 4)
		color = 0xFFFFFF;
	else
		color = 0x000000;
	if (data->dda.side == 1)
		color /= 2;
	for (int y = wall_start; y < wall_end; y++)
		img_pix_put(&data->img, x, y, color);
}*/

void	render_map(t_data *data, int x)
{
	int	buffer[WIN_HEIGHT][WIN_WIDTH];
	double	wallX;
	int		texX;
	int		texY;
	double	step;
	double	texPos;
	int wall_height;
	int wall_start;
	int wall_end;
	int color;

	if (data->dda.wallDist == 0)
		data->dda.wallDist++;
	wall_height = (int) (WIN_HEIGHT / data->dda.wallDist);
	wall_start = -wall_height / 2 + WIN_HEIGHT / 2;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = wall_height / 2 + WIN_HEIGHT / 2;
	if (wall_end >= WIN_HEIGHT)
		wall_end = WIN_HEIGHT - 1;
	if (data->dda.side == 0)
		wallX = data->p.y + data->dda.wallDist * data->vec.rayY;
	else
		wallX = data->p.x + data->dda.wallDist * data->vec.rayX;
	wallX -= floor(wallX);
	texX = (int) (wallX * (double) data->tex.tex_width);
	if (data->dda.side == 0 && data->vec.rayX > 0)
		texX = data->tex.tex_width - texX - 1;
	if (data->dda.side == 1 && data->vec.rayY < 0)
		texX = data->tex.tex_width - texX - 1;
	step = 1.0 * data->tex.tex_width / wall_height;
	texPos = (wall_start - WIN_HEIGHT / 2 + wall_height / 2) * step;
	for (int y = wall_start; y < wall_end; y++)
	{
		texY = (int) texPos & (data->tex.tex_height - 1);
		texPos += step;
		color = data->tex.img.addr[data->tex.tex_height * texY + texX];
	//	printf("%i\n", color);
		if (data->dda.side == 1)
			color = (color >> 1) & 8355711;
		data->img.addr[y * WIN_WIDTH + x] = color;
	}
}

int draw(t_data *data)
{
	void    **textures;
	double  cameraX;
	double  rayX;
	double  rayY;

	if (!data->win_ptr)
		return (1);
	for (int x = 0; x < WIN_WIDTH; x++)
	{
		cameraX = 2 * x / (double)WIN_WIDTH - 1;
		rayX = data->p.dirX + data->vec.planeX * cameraX * data->p.direction;
		rayY = data->p.dirY + data->vec.planeY * cameraX * data->p.direction;
		dda(data, rayX, rayY);
		render_map(data, x);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
/*	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);*/
	return (0);
}

//change player pos to variable
void    set_dir(t_data *data)
{
	if (map[22][12] == 'N')
	{
		data->p.dirX = 0;
		data->p.dirY = 1;
	}
	else if (map[22][12] == 'S')
	{   data->p.dirX = 0;
		data->p.dirY = -1;
		data->p.direction = -1;
	}
	else if (map[22][12] == 'E')
	{
		data->p.dirX = 1;
		data->p.dirY = 0;
		data->p.direction = -1;
	}
	else if (map[22][12] == 'W')
	{
		data->p.dirX = -1;
		data->p.dirY = 0;
	}
}

void    set_plane(t_data *data)
{
	if (data->p.dirX == 0)
	{
		data->vec.planeX = tan(FOV);
		data->vec.planeY =  0;
	}
	else
	{
		data->vec.planeX = 0;
		data->vec.planeY = tan(FOV);
	}
}

void    have_fun(t_data *data)
{
	data->p.x = 22;
	data->p.y = 12;
	data->p.direction = 1;
	data->p.move_speed = 1.0;
	data->p.rotation_speed = 3.0 * (M_PI / 180);
	set_dir(data);
	set_plane(data);
	map[22][12] = 0;
	load_textures(data);
	mlx_loop_hook(data->mlx_ptr, &draw, data);
}

int main(int argc, char **argv)
{
	t_data  data;

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
