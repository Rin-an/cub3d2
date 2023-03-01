/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:21:10 by ssadiki           #+#    #+#             */
/*   Updated: 2023/03/01 03:09:25 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "get_next_line/get_next_line.h"
# define MAP_HEIGHT 24
# define MAP_WIDTH 24
# define WIN_WIDTH 1024
# define WIN_HEIGHT 1024

/* TO REMOVE */
int	map[MAP_WIDTH][MAP_HEIGHT];

typedef struct s_img
{
	void	*mlx_img;
	int		*addr;
	int		line_len;
	int		endian;
	int		bpp;
}	t_img;

typedef struct s_text
{
	int		tex_width;
	int		tex_height;
	int		wall_height;
	int		wall_start;
	int		wall_end;
	int		wallx;
	int		tex_x;
	int		tex_y;
	double	tex_step;
	double	tex_pos;
	t_img	img;
}	t_text;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		move_speed;
	double		rotation_speed;
	int			direction;
}	t_player;

typedef struct s_vec
{
	double	plane_x;
	double	plane_y;
	double	ray_x;
	double	ray_y;
}	t_vec;

typedef struct s_dda
{
	int		side;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	dx;
	double	dy;
	int		step_x;
	int		step_y;
	double	walldist;
}	t_dda;

typedef struct s_keypress
{
	int	right;
	int	left;
	int	up;
	int	down;
	int	r_right;
	int	r_left;
	int	reset;
}	t_keypress;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			x;
	t_img		img;
	t_player	p;
	t_vec		vec;
	t_text		tex;
	t_dda		dda;
	t_keypress	kp;
}	t_data;

/* EXECUTION */
/*           */
//INIT SETTINGS
void	init_mlx(t_data *data);
void	init_settings(t_data *data);
void	set_plane(t_data *data);
void	set_dir(t_data *data);

//DDA
void	dda(t_data *data);

//HOOKS
void	hooks(t_data *data);
int		keypress(int keycode, t_data *data);
int		keyrelease(int keycode, t_data *data);
void	reset_settings(t_data *data);
int		draw(t_data *data);

//EXIT
void	exit_keypress(t_data *data);
int		exit_button(t_data *data);

//PLAYER MOVEMENTS
void	up_down(t_data *data);
void	left_right(t_data *data);
void	rotate(t_data *data, double rotation_speed);
void	move_player(t_data *data);

//RENDER MAP
void	render_map(t_data *data, int x);
void	floor_ceiling(t_data *data);
void	load_textures(t_data *data);

//UTILS
void	img_pix_put(t_img *img, int x, int y, int color);

#endif
