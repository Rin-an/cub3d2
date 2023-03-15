/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:21:10 by ssadiki           #+#    #+#             */
/*   Updated: 2023/03/03 03:09:32 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include "get_next_line/get_next_line.h"
# define WIN_WIDTH 1024
# define WIN_HEIGHT 1024

typedef struct s_info
{
	int	len;
	int	j;
}	t_info;

typedef struct s_point
{
	int	j;
	int	i;
}	t_point;

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
	char		*north_texture;
	char		*west_texture;
	char		*east_texture;
	char		*south_texture;
	int			floor_color;
	int			ceiling_color;
	char		**map;
	char		**lines;
	int			map_height;
	t_player	p;
	t_img		img;
	t_vec		vec;
	t_text		tex;
	t_dda		dda;
	t_keypress	kp;
}	t_data;

/* PARSING */
/*         */

//parsing_functions

int		check_dup(bool *exist);
int		parse_function(t_data *mlx);
void	read_file(int fd, t_data *mlx);
int		check_file_extension(char *s, char *extension, int *fd);

//color functions
int		to_color(char **str);
int		check_color(char **str);
int		color_stock(char c, char *str, t_data *mlx);
int		parse_color(char **splited, char *str, bool *exist, t_data *mlx);

//parsing_utils

void	free_mlx(t_data *mlx);
void	free_map(char **map);
void	clear_splited(char **s);
size_t	ft_maplen(char **s);
int		ft_strlenew(char **s);
void	display_message_error(int if_error);

// check_identif functions

int		read_textures(char *texture, char identif, t_data *mlx);
int		fill_identif(bool *exist, char *str, t_data *mlx, char c);
int		check_identifiers(char **str, bool *exist, t_data *mlx);
int		check_fun(char *line, bool *exist, t_data *mlx);
int		check_function(char **lines, int *j, bool *exist, t_data *mlx);

//check_map_functions

int		check_map_suite(char **str, t_info info, int *flag, t_data *mlx);
int		check_first_last_maplines(int len_first, int len_map, char **str);
int		check_map(char **str, t_data *mlx);
void	ft_check_map_end(char **str, t_data *mlx);
int		player_check(char c, int *existence, t_data *mlx, t_point point);
int		check_borders(char **str, int *len);

//utils

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s);
char	**ft_split(const char *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_calloc(size_t count, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_atoi(const char *str);
int		ft_strlen2(char **s);

/* EXECUTION */
/*           */
//INIT SETTINGS
void	init_mlx(t_data *data);
void	init_mlx2(t_data *data);
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
