/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:18:37 by aouchaad          #+#    #+#             */
/*   Updated: 2023/10/06 12:32:29 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h> 
# include "../libft/libft.h"
# include "/Users/hoigag/MLX42/MLX42.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>

# define BLOCK_ZIZE 64
# define MAP_ELEMENTS 6
# define MOVE_SPEED 7
# define WIDTH 1500
# define HEIGHT 1050

typedef struct s_textrs
{
	mlx_texture_t	*ea_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*no_texture;
}	t_textrs;

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

typedef struct s_ray
{
	int		index;
	float	hor_intercept_x;
	float	hor_intercept_y;
	float	vert_intercept_x;
	float	vert_intercept_y;
	int		first_hit;
	float	ray_long;
	float	ray_angle;
}	t_ray;

typedef struct s_vars
{
	float	xstep;
	float	ystep;
	float	xintercept;
	float	yintercept;
	float	nextx;
	float	nexty;
	float	vert_inter_x;
	float	vert_inter_y;
	float	horiz_iter_x;
	float	horiz_iter_y;
	float	vert_dist;
	float	horz_dist;
	float	dx;
	float	dy;
	int		var;
	int		fouandwall;
	float	starty;
	float	textur_x;
	float	textur_y;
	float	textur_inc;
	float	walltoppixel;
}	t_vars;

typedef struct s_glob
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_ray		*ray;
	t_textrs	txtrs;
	float		rotation_speed;
	int			redraw;
	float		start_x;
	float		start_y;
	float		end_x;
	float		end_y;
	float		vue_angle;
	float		rays_angle;
	int			num_rays;
	float		angle_incr;
	char		**map;
	int			width;
	int			height;
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
}	t_glob;

mlx_texture_t	*shoose_texture(t_ray ray, t_glob *glob);
void			wich_vue(char vue, t_glob *glob);
void			draw_map(t_glob *glob);
void			normalize_angle(float *angle);
void			init_func(t_glob *glob);
void			cast_ray(t_glob *glob, int i);
void			cast_all_rays(t_glob *glob);
void			key_handler(void *param);
void			draw_sky(t_glob *glob);
void			draw_floor(t_glob *glob);
void			error_log(char *err);
void			get_map(t_glob *data);
void			get_map_data(t_glob *data);
void			remove_new_line(char **line);
void			free_2d(char **array);
void			is_map_valid(t_glob *data);
void			parse_info(t_glob *data);
void			set_player_dir(char **dir, char *path);
void			scene_parser(t_glob *data, char *file, int argc);
void			free_func(t_glob *glob);
void			creat_textures(t_glob *glob);
void			delete_textures(t_glob *glob);
void			change_first_occurenc(char **str, char c, char new_c);
float			distance(float x1, float x2, float y1, float y2);
float			horizontal_intercept(t_glob *glob, t_ray *ray);
float			vertical_intercept(t_glob *glob, t_ray *ray);
char			*get_line(int fd);
int				ray_facing_right(float ray_angle);
int				ray_facing_down(float ray_angle);
int				can_move(t_glob *glob, int key);
int				is_wall(t_glob *glob, float end_x, float end_y);
int				longest_line(t_glob *glob);
int				map_size(t_glob *glob);
int				get_rgba(int r, int g, int b, int a);
int				is_file_name_valid(char *file_name);
int				is_empty_line(char *line);
int				get_scene_elements(t_glob *data);
int				get_2d_arr_size(char **arr);
int				ft_atoi_v2(const char *str);
int				get_color_from_textrs(int x, int y, mlx_texture_t *texture);

#endif
