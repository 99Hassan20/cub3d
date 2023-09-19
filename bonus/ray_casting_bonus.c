/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:53:22 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/19 19:32:06 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_wall(t_glob *glob, float end_x, float end_y)
{
	float	x;
	float	y;

	if (end_x < 0 || end_x >= glob->width || end_y < 0 || end_y >= glob->height)
		return (1);
	x = floor(end_x / BLOCK_ZIZE);
	y = floor(end_y / BLOCK_ZIZE);
	if (y >= glob->map_height)
		return (1);
	if (x >= ft_strlen(glob->map[(int)y]))
		return (1);
	if (glob->map[(int)y][(int)x] == '1')
		return (1);
	return (0); 
}

int	get_color_from_textrs(int x, int y, mlx_texture_t *texture)
{
	int	i;

	i = (x * 4) + ((y * 4) * texture->width);
	// return(get_rgba(get_r(texture->pixels[i]), get_g(texture->pixels[i + 1]),
	// get_b(texture->pixels[i + 2]), get_a(texture->pixels[i + 3])));
	return (texture->pixels[i] << 24
		| texture->pixels[i + 1] << 16
		| texture->pixels[i + 2] << 8 | texture->pixels[i + 3]);
}

mlx_texture_t	*shoose_texture(t_ray ray, t_glob *glob)
{
	if (ray.first_hit == '2'
		&& (ray.ray_angle < M_PI_2 || ray.ray_angle > (3 * M_PI_2)))
		return (glob->txtrs.ea_texture);
	else if (ray.first_hit == '2'
		&& (ray.ray_angle >= M_PI_2 && ray.ray_angle <= (3 * M_PI_2)))
		return (glob->txtrs.we_texture);
	else if (ray.first_hit == '1'
		&& (ray.ray_angle >= 0 && ray.ray_angle <= M_PI))
		return (glob->txtrs.no_texture);
	return (glob->txtrs.so_texture);
}

void	draw_wall(t_glob *glob, float wall_height, t_ray ray)
{
	float	starty;
	float	textur_x;
	float	textur_y;
	float	textur_inc;
	float	walltoppixel;
	int		this = 0;

	this = 0;
	// int factor;
	textur_inc = (float)BLOCK_ZIZE / wall_height;
	// textur_y = 0;
	// if (ray.first_hit == 2)
	// 	textur_x = (glob->txtrs.ea_texture->width / BLOCK_ZIZE) * (ray.vert_intercept_y - ((int)(ray.vert_intercept_y / BLOCK_ZIZE) * BLOCK_ZIZE));
	// else
	// 	textur_x = (texture->wid / BLOCK_ZIZE) * (ray.hor_intercept_x - ((int)(ray.hor_intercept_x / BLOCK_ZIZE) * BLOCK_ZIZE));
	
	// if (textur_x > texture->width)
	// {w
	// 	factor = (int)textur_x % (int)texture->width;
	// 	factor *= texture->width;
	// 	// textur_x /= factor;
	// 	textur_x = textur_x - factor;
	// }
	// if (textur_x < 0)
	// 	textur_x = 0;
	//////////////////////////////////////////////////////////////
	if (ray.first_hit == '2')
	{
		this = 1;
		textur_x = (int)ray.vert_intercept_y % BLOCK_ZIZE;
	}
	else
	{
		// printf("%f\n", ray.x_intersection);
		textur_x = (int)ray.hor_intercept_x % BLOCK_ZIZE;
	}
	///////////////////////////////////////////////////////////////
	walltoppixel = ((float)HEIGHT / 2) - ((float)wall_height / 2); 
	starty = walltoppixel; 
	if (starty < 0)
		starty = 0;
	while (starty <= ((float)HEIGHT / 2) + ((float)wall_height / 2)) 
	{
		textur_y = (starty - walltoppixel) * textur_inc;
		if (textur_y >= BLOCK_ZIZE)
			textur_y = 0;
		if (starty >= HEIGHT) 
			break ;
			// printf("texturex = %f\n", textur_x);
			// printf("texturey = %f\n", textur_y);
		mlx_put_pixel(glob->image, (glob->num_rays - (ray.index + 1)), starty,
			get_color_from_textrs(textur_x, textur_y, shoose_texture(ray, glob)));
		starty++;
		textur_y += textur_inc;
	}
}

void	creat_textures(t_glob *glob)
{
	glob->txtrs.ea_texture = mlx_load_png(glob->ea);
	glob->txtrs.we_texture = mlx_load_png(glob->we);
	glob->txtrs.so_texture = mlx_load_png(glob->so);
	glob->txtrs.no_texture = mlx_load_png(glob->no);
	if (!glob->txtrs.ea_texture || !glob->txtrs.we_texture || \
		!glob->txtrs.so_texture || !glob->txtrs.no_texture)
		error_log("fail to load png file");
}

void	wall_projection(t_glob *glob)
{
	int	i;
	float		wall_height;
	float	dis_proj_plane;
	// float textur_x;
	

	i = glob->num_rays - 1;
	// texture = mlx_load_png("/Users/aouchaad/Desktop/wall.png");
	// textur_x = texture->width - 1;
	dis_proj_plane = ((float)WIDTH / 2) / tanf(glob->rays_angle / 2);  
	while (i >= 0)
	{
		wall_height = BLOCK_ZIZE / glob->ray[i].ray_long \
		* dis_proj_plane;
		draw_wall(glob, wall_height, glob->ray[i]);
		i--;
		// textur_x--;
		// if (textur_x < 0)
		// 	textur_x = texture->width;
	}
}

void	cast_ray(t_glob *glob, int i)
{
	t_vars	vars;

	vars.horz_dist = horizontal_intercept(glob, &(glob->ray[i]));
	vars.vert_dist = vertical_intercept(glob, &(glob->ray[i]));
	if (vars.horz_dist < vars.vert_dist)
	{
		glob->ray[i].ray_long = vars.horz_dist * \
		cosf(glob->ray[i].ray_angle - glob->vue_angle);
		glob->ray[i].first_hit = '1';
	}
	else
	{
		glob->ray[i].ray_long = vars.vert_dist * \
		cosf(glob->ray[i].ray_angle - glob->vue_angle);
		glob->ray[i].first_hit = '2';
	}
}

void	delete_textures(t_glob *glob)
{
	mlx_delete_texture(glob->txtrs.ea_texture);
	mlx_delete_texture(glob->txtrs.we_texture);
	mlx_delete_texture(glob->txtrs.no_texture);
	mlx_delete_texture(glob->txtrs.so_texture);
}

void	cast_all_rays(t_glob *glob)
{
	int		i;
	float	new_angle;

	i = 0;
	new_angle = glob->vue_angle + (30 * (M_PI / 180));
	// normalize_angle(&new_angle);
	while (i < glob->num_rays)
	{
		normalize_angle(&new_angle);
		glob->ray[i].index = i;
		glob->ray[i].ray_angle = new_angle;
		cast_ray(glob, i);
		new_angle -= glob->angle_incr;
		i++;
	}
	wall_projection(glob);
}
