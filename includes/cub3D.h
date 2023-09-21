/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:05:02 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/21 17:40:22 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h> 
# include "../libft/libft.h"
# include "/Users/aouchaad/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>

# define BLOCK_ZIZE 64
# define MAP_ELEMENTS 6
# define MOVE_SPEED 7
# define WIDTH 1500
# define HEIGHT 1200

typedef struct s_textrs
{
	mlx_texture_t	*ea_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*closed_door;
	mlx_texture_t	*opend_door;
	mlx_texture_t	*gun_txtr;
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
	int		is_door;
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
	float	steps;
	float	x_inc;
	float	y_inc;
	float	x_pixel;
	float	y_pixel;
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
	int			door_closed;
	float		rotation_speed;
	float		start_x;
	int			redraw;
	float		start_y;
	float		end_x;
	float		end_y;
	float		vue_angle;
	float		rays_angle;
	int			num_rays;
	int			old_mouse_posx;
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

void			end_point(t_glob *glob, float ray_long, float angle);
void			wich_vue(char vue, t_glob *glob);
void			draw_line(t_glob *glob, float end_x, float end_y, int color);
int				ray_facing_right(float ray_angle);
int				ray_facing_down(float ray_angle);
void			draw_rect(int colon, int line, int color, t_glob *glob);
float			distance(float x1, float x2, float y1, float y2);
void			put_player(t_glob *glob);
void			normalize_angle(float *angle);
void			draw_map(t_glob *glob);
int				can_move(t_glob *glob, int key);
void			init_func(t_glob *glob);
int				is_wall(t_glob *glob, float end_x, float end_y);
float			horizontal_intercept(t_glob *glob, t_ray *ray);
void			cast_ray(t_glob *glob, int i);
void			cast_all_rays(t_glob *glob);
void			key_handler(void *param);
int				longest_line(t_glob *glob);
int				map_size(t_glob *glob);
float			vertical_intercept(t_glob *glob, t_ray *ray);
void			draw_sky(t_glob *glob);
void			draw_floor(t_glob *glob);
void			draw_minimap(t_glob *glob);
int				get_rgba(int r, int g, int b, int a);
void			error_log(char *err);
int				is_file_name_valid(char *file_name);
void			get_map(t_glob *data);
void			get_map_data(t_glob *data);
int				is_empty_line(char *line);
void			remove_new_line(char **line);
int				get_scene_elements(t_glob *data);
void			free_2d(char **array);
void			is_map_valid(t_glob *data);
char			*get_line(int fd);
int				get_2d_arr_size(char **arr);
int				ft_atoi_v2(const char *str);
void			parse_info(t_glob *data);
void			set_player_dir(char **dir, char *path);
void			scene_parser(t_glob *data, char *file, int argc);
void			free_func(t_glob *glob);
int				get_r(int rgba);
int				get_g(int rgba);
int				get_b(int rgba);
int				get_a(int rgba);
void			creat_textures(t_glob *glob);
void			delete_textures(t_glob *glob);
mlx_texture_t	*shoose_texture(t_ray ray, t_glob *glob);
int				get_color_from_textrs(int x, int y, mlx_texture_t *texture);
void	put_gun(t_glob *glob, mlx_image_t **img);

#endif
