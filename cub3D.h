/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:05:02 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/07 16:17:38 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h> 
# include "libft/libft.h"
#include "/Users/aouchaad/MLX42/include/MLX42/MLX42.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
# include <fcntl.h>

# define BLOCK_ZIZE 80
# define MAP_ELEMENTS 6
// # define WIDTH 2000
// # define HEIGHT 1120
# define MOVE_SPEED 10
# define ROTATION_SPEED (2 * (M_PI / 180))

// typedef struct s_map
// {
// 	char	**the_map;
// 	// int 	map_num_rows;
// 	// int		map_num_cols;
// 	// char	**floor_color;
// 	char	**ceil_color;
// }	t_map;

typedef struct s_element
{
	char	*type;
	char	*value;
}	t_element;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_vars
{
	float	xstep;
	float	ystep;
	float	xintercept;
	float	yintercept;
	float	nextx;
	float	nexty;
	float	vertInterX;
	float	vertInterY;
	float	horizIterX;
	float	horizIterY;
	float	vert_dist;
	float	horz_dist;
	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;
	float	x_pixel;
	float	y_pixel;
	int		var;
	int		fouandwall;
}	t_vars;

typedef struct s_glob
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	float			start_x;
	float			start_y;
	float			end_x;
	float			end_y;
	float		vue_angle;
	float		rays_angle;
	int			num_rays;
	float			*rays_long;
	// float			*vrtcl_intrsction;
	// float			*horiz_intrsction;
	float		angle_incr;
	char 		**map;
	int width;
	int height;
	char		*file_name;
	int			map_height;
	char		**map_info;
	t_element	*elements;
	t_color		floor;
	t_color		ceiling;
	char		*so;
	char		*ea;
	char		*we;
	char		*no;
	// void	*init_ptr;
	// void	*win_ptr;
	// void	*mlx_img;
	// void	*img_addr;
	// int		bits_per_pixel;
	// int		line_length;
	// int		endian;
	// int		win_width;
	// int		win_height;
	
}	t_glob;

void	fill_map(t_glob *glob);
void	wich_vue(char vue, t_glob *glob);
void	end_point(t_glob *glob, float ray_long, float angle);
void	draw_line(t_glob *glob, float end_x, float end_y, int color);
int	ray_facing_right(float ray_angle);
int ray_facing_down(float ray_angle);
void	draw_rect(int colon, int line, int color, t_glob *glob);
void	draw_grid(int colon, int line, int color, t_glob *glob);
float	distance(float x1, float x2, float y1, float y2);
void	put_player(t_glob *glob);
void	normalize_angle(float *angle);
void	draw_mini_map(t_glob *glob);
int	can_move(t_glob *glob, int key);
void	init_func(t_glob *glob);
int is_wall(t_glob *glob, float end_x, float end_y);
float	horizontal_intercept(t_glob *glob, float ray_angle, float *wallhitx, float *wallhity);
void	cast_ray(t_glob *glob, float ray_angle, float i);
void	cast_all_rays(t_glob *glob);
void key_handler(void *param);
void	cast_the_rays(t_glob *glob);
void	draw_rectangle(t_glob *glob, int line, int colon, int wall_height, int wall_width);
int longest_line(t_glob *glob);
int map_size(t_glob *glob);
float	vertical_intercept(t_glob *glob, float ray_angle, float *wallhitx, float *wallhity);
void	draw_sky(t_glob *glob);
void	draw_floor(t_glob *glob);
void	draw_map(t_glob *glob);
void	error_log(char *err);
int		is_file_name_valid(char *file_name);
void	get_map(t_glob *data);
void	get_map_data(t_glob *data);
int		is_empty_line(char *line);
void	remove_new_line(char **line);
int		get_scene_elements(t_glob *data);
void	free_2d(char **array);
void	is_map_valid(t_glob *data);
char	*get_line(int fd);
int		get_2d_arr_size(char **arr);
int		ft_atoi_v2(const char *str);
void	set_colors(t_color *color, char *str);
void	parse_info(t_glob *data);
void	set_player_dir(char **dir, char *path);
void	scene_parser(t_glob *data, char *file, int argc);
// void	draw_line2(t_glob *glob, float start_x, float start_y, float end_x, float end_y);

#endif
