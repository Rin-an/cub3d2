/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:59:44 by ssadiki           #+#    #+#             */
/*   Updated: 2023/03/01 03:32:26 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void    init_mlx(t_data *data)
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
}

void    img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	img->addr = (int *) mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
	pixel = (char *) img->addr + (img->line_len * y + x * (img->bpp / 8));
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
/*int map[MAP_WIDTH][MAP_HEIGHT]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,'E',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};*/


//FOR THE SAKE OF MY SANITY

// HOOKS

/*void    exit_keypress(t_data *data)
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

void move_player(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (data->kp.up == 1) //up move
	{
		if (map[(int) (data->p.x + data->p.dir_x* data->p.move_speed)][(int) data->p.y] == 0)
			data->p.x += data->p.dir_x * data->p.move_speed;
		if (map[(int) data->p.x][(int) (data->p.y + data->p.dir_y * data->p.move_speed)] == 0)
			data->p.y += data->p.dir_y * data->p.move_speed;
	}
	else if (data->kp.down == 1) // down move
	{
		if (map[(int) (data->p.x - data->p.dir_x * data->p.move_speed)][(int) data->p.y] == 0)
			data->p.x -= data->p.dir_x * data->p.move_speed;
		if (map[(int) data->p.x][(int) (data->p.y - data->p.dir_y * data->p.move_speed)] == 0)
			data->p.y -= data->p.dir_y * data->p.move_speed;
	
	}
	else if (data->kp.left == 1) //left move
	{
		if (map[(int) (data->p.x - data->vec.plane_x * data->p.move_speed)][(int) data->p.y] == 0)
			data->p.x -= data->vec.plane_x * data->p.move_speed * data->p.direction;
		if (map[(int) data->p.x][(int) (data->p.y - data->vec.plane_y * data->p.move_speed)] == 0)
			data->p.y -= data->vec.plane_y * data->p.move_speed * data->p.direction;
		
	}
	else if (data->kp.right == 1) // right move
	{
		if (map[(int) (data->p.x + data->vec.plane_x * data->p.move_speed)][(int) data->p.y] == 0)
			data->p.x += data->vec.plane_x * data->p.move_speed * data->p.direction;
		if (map[(int) data->p.x][(int) (data->p.y + data->vec.plane_y * data->p.move_speed)] == 0)
			data->p.y += data->vec.plane_y * data->p.move_speed * data->p.direction;
		
	}
	else if (data->kp.r_left == 1)
	{
		double  tmpdir = data->p.dir_x;
		double  tmpplane = data->vec.plane_x;
		data->p.dir_x = data->p.dir_x * cos(data->p.rotation_speed) - data->p.dir_y * sin(data->p.rotation_speed);
		data->p.dir_y = tmpdir * sin(data->p.rotation_speed) + data->p.dir_y * cos(data->p.rotation_speed);
		data->vec.plane_x = data->vec.plane_x * cos(data->p.rotation_speed) - data->vec.plane_y * sin(data->p.rotation_speed);
		data->vec.plane_y = tmpplane * sin(data->p.rotation_speed) + data->vec.plane_y * cos(data->p.rotation_speed);
	}
	else if (data->kp.r_right == 1)
	{
		double  tmpdir = data->p.dir_x;
		double  tmpplane = data->vec.plane_x;
		data->p.dir_x = data->p.dir_x * cos(-data->p.rotation_speed) - data->p.dir_y * sin(-data->p.rotation_speed);
		data->p.dir_y = tmpdir * sin(-data->p.rotation_speed) + data->p.dir_y * cos(-data->p.rotation_speed);
		data->vec.plane_x = data->vec.plane_x * cos(-data->p.rotation_speed) - data->vec.plane_y * sin(-data->p.rotation_speed);
		data->vec.plane_y = tmpplane * sin(-data->p.rotation_speed) + data->vec.plane_y * cos(-data->p.rotation_speed);
	}
	else if (data->kp.reset == 1)
	{
		data->p.x = 22;
		data->p.y = 12;
		data->p.dir_x = -1;
		data->p.dir_y = 0;
		data->vec.plane_y = 0.66;
		data->vec.plane_x = 0;
		data->p.direction = 1;
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
}

int keypress(int keycode, t_data *data)
{
	if (keycode == 53)
		exit_keypress(data);
	else if (keycode == 13) //up move
		data->kp.up = 1;
	else if (keycode == 1) // down move
		data->kp.down = 1;
	else if (keycode == 0) //left move
		data->kp.left = 1;
	else if (keycode == 2) // right move
		data->kp.right = 1;
	else if (keycode == 123)
		data->kp.r_left = 1;
	else if (keycode == 124)
		data->kp.r_right = 1;
	else if (keycode == 15)
		data->kp.reset = 1;
	else
		return (1);
	move_player(data);
	return (0);
}

int keyrelease(int keycode, t_data *data)
{
	if (keycode == 13)
		data->kp.up = 0;
	else if (keycode == 1)
		data->kp.down = 0;
	else if (keycode == 0)
		data->kp.left = 0;
	else if (keycode == 2)
		data->kp.right = 0;
	else if (keycode == 123)
		data->kp.r_left = 0;
	else if (keycode == 124)
		data->kp.r_right = 0;
	else if (keycode == 15)
		data->kp.reset = 0;
	return (0);
}

void	hooks(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 0, &keypress, data);
	mlx_hook(data->win_ptr, 3, 0, &keyrelease, data);
	mlx_hook(data->win_ptr, 17, 0, &exit_button, data);
//	mlx_loop(data->mlx_ptr);
}
//END OF HOOKS

void    load_textures(t_data *data)
{
	//West
	if (data->dda.side == 0 && data->dda.step_x == -1)
		data->tex.img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/purplestone.xpm", &data->tex.tex_width, &data->tex.tex_height);
	//East
	else if (data->dda.side == 0 && data->dda.step_x == 1)
		data->tex.img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/redbrick.xpm", &data->tex.tex_width, &data->tex.tex_height);
	//North
	else if (data->dda.side == 1 && data->dda.step_y == 1)
		data->tex.img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/colorstone.xpm", &data->tex.tex_width, &data->tex.tex_height);
	//South
	else if (data->dda.side == 1 && data->dda.step_y == -1)
		data->tex.img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/eagle.xpm", &data->tex.tex_width, &data->tex.tex_height);
	data->tex.img.addr = (int *)mlx_get_data_addr(data->tex.img.mlx_img, &data->tex.img.line_len, &data->tex.img.bpp, &data->tex.img.endian);
}

void	render_map(t_data *data, int x)
{
	//int data->tex.wall_height;
	//int data->tex.wall_start;
	//int data->tex.wall_end;
	double	wallX;
//	int		data->tex.tex_x;
//	int		data->tex.tex_y;
//	double	data->tex.tex_step;
//	double	data->tex.tex_pos;
	int color;

	if (data->dda.walldist == 0)
		data->dda.walldist++;
	data->tex.wall_height = (int) (WIN_HEIGHT / data->dda.walldist);
	data->tex.wall_start = -data->tex.wall_height / 2 + WIN_HEIGHT / 2;
	if (data->tex.wall_start < 0)
		data->tex.wall_start = 0;
	data->tex.wall_end = data->tex.wall_height / 2 + WIN_HEIGHT / 2;
	if (data->tex.wall_end >= WIN_HEIGHT)
		data->tex.wall_end = WIN_HEIGHT - 1;
	if (data->dda.side == 0)
		wallX = data->p.y + data->dda.walldist * data->vec.ray_y;
	else
		wallX = data->p.x + data->dda.walldist * data->vec.ray_x;
	wallX -= (int)((wallX));
	data->tex.tex_x = (int) (wallX * (double) data->tex.tex_width);
	if (data->dda.side == 0 && data->vec.ray_x > 0)
		data->tex.tex_x = data->tex.tex_width - data->tex.tex_x - 1;
	if (data->dda.side == 1 && data->vec.ray_y < 0)
		data->tex.tex_x = data->tex.tex_width - data->tex.tex_x - 1;
	data->tex.tex_step = 1.0 * data->tex.tex_height / data->tex.wall_height;
	data->tex.tex_pos = (data->tex.wall_start - WIN_HEIGHT / 2 + data->tex.wall_height / 2) * data->tex.tex_step;
	for (int y = data->tex.wall_start; y < data->tex.wall_end; y++)
	{
		data->tex.tex_y = (int) data->tex.tex_pos & (data->tex.tex_height - 1);
		data->tex.tex_pos += data->tex.tex_step;
		color = data->tex.img.addr[data->tex.tex_height * data->tex.tex_y + data->tex.tex_x];
		if (data->dda.side == 1)
			color = (color >> 1) & 8355711;
		data->img.addr[y * WIN_WIDTH + x] = color;
	}
}

void	floor_ceiling(t_data *data)
{
	int		floor_color;
	int		ceiling_color;

	floor_color = 0x223322;
	ceiling_color = 0x222222;
	for (int y = 0; y < WIN_HEIGHT / 2; y++)
	{
		for(int x = 0; x < WIN_WIDTH; x++)
			img_pix_put(&data->img, x, y, ceiling_color);
	}
	for (int y = WIN_HEIGHT / 2; y < WIN_HEIGHT; y++)
	{
		for(int x = 0; x < WIN_WIDTH; x++)
			img_pix_put(&data->img, x, y, floor_color);
	}
}

int draw(t_data *data)
{
	double  cameraX;

	if (!data->win_ptr)
		return (1);
//	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	floor_ceiling(data);
	for (int x = 0; x < WIN_WIDTH; x++)
	{
		cameraX = 2 * x / (double)WIN_WIDTH - 1;
		data->vec.ray_x = data->p.dir_x + data->vec.plane_x * cameraX * data->p.direction;
		data->vec.ray_y = data->p.dir_y + data->vec.plane_y * cameraX * data->p.direction;
		dda(data);
		load_textures(data);
		render_map(data, x);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
//	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
//	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	return (0);
}

//change player pos to variable
void    set_dir(t_data *data)
{
	if (map[(int) data->p.x][(int) data->p.y] == 'N')
	{
		data->p.dir_x = 0.0;
		data->p.dir_y = 1.0;
//		data->vec.plane_x = 0.66;
//		data->vec.plane_y =  0.0;
	}
	else if (map[(int) data->p.x][(int) data->p.y] == 'S')
	{   
		data->p.dir_x = 0.0;
		data->p.dir_y = -1.0;
//		data->vec.plane_x = -0.66;
//		data->vec.plane_y =  0.0;
		data->p.direction = -1;
	}
	else if (map[(int) data->p.x][(int) data->p.y] == 'E')
	{
		data->p.dir_x = 1.0;
		data->p.dir_y = 0.0;
//		data->vec.plane_y = -0.66;
//		data->vec.plane_x =  0.0;
		data->p.direction = -1;
	}
	else if (map[(int) data->p.x][(int) data->p.y] == 'W')
	{
		data->p.dir_x = -1.0;
		data->p.dir_y = 0.0;
//		data->vec.plane_y = 0.66;
//		data->vec.plane_x =  0.0;
	}
}

void    set_plane(t_data *data)
{
	if (data->p.dir_x == 0)
	{
		data->vec.plane_x = 0.66;
		data->vec.plane_y =  0;
	}
	else
	{
		data->vec.plane_x = 0;
		data->vec.plane_y= 0.66;
	}
}

void    have_fun(t_data *data)
{
	data->p.x = 22;
	data->p.y = 12;
	data->kp.up = 0;
	data->kp.down = 0;
	data->kp.left = 0;
	data->kp.right = 0;
	data->kp.r_right = 0;
	data->kp.r_left = 0;
	data->kp.reset = 0;
	data->p.direction = 1;
	data->p.move_speed = 0.4;
	data->p.rotation_speed = 3.0 * (M_PI / 180);
//	data->p.rotation_speed = 0.2;
	set_dir(data);
	set_plane(data);
	map[(int) data->p.x][(int) data->p.y] = 0;
	mlx_loop_hook(data->mlx_ptr, &draw, data);
	hooks(data);
	mlx_loop(data->mlx_ptr);
}*/

void	have_fun(t_data *data)
{
	init_settings(data);
	mlx_loop_hook(data->mlx_ptr, &draw, data);	
	hooks(data);
	mlx_loop(data->mlx_ptr);
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
	/*	mlx_loop_hook(data.mlx_ptr, &draw, &data);
		hooks(&data);
		mlx_loop(data.mlx_ptr);*/
		have_fun(&data);
	//	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	//	free(data.mlx_ptr);
	}
	return (0);
}
