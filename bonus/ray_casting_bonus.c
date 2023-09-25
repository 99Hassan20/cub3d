/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:53:22 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/25 12:43:59 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	draw_wall(t_glob *glob, float wall_height, t_ray ray)
{
	t_vars	vars;

	vars.textur_inc = (float)BLOCK_ZIZE / wall_height;
	if (ray.first_hit == '2')
		vars.textur_x = (int)ray.vert_intercept_y % BLOCK_ZIZE;
	else
		vars.textur_x = (int)ray.hor_intercept_x % BLOCK_ZIZE;
	vars.walltoppixel = ((float)HEIGHT / 2) - ((float)wall_height / 2); 
	vars.starty = vars.walltoppixel; 
	if (vars.starty < 0)
		vars.starty = 0;
	while (vars.starty <= ((float)HEIGHT / 2) + ((float)wall_height / 2)) 
	{
		vars.textur_y = (vars.starty - vars.walltoppixel) * vars.textur_inc;
		if (vars.textur_y >= BLOCK_ZIZE)
			vars.textur_y = 0;
		if (vars.starty >= HEIGHT) 
			break ;
		mlx_put_pixel(glob->image, (glob->num_rays - (ray.index + 1)), \
		vars.starty, get_color_from_textrs(vars.textur_x, vars.textur_y, \
		shoose_texture(ray, glob)));
		vars.starty++;
		vars.textur_y += vars.textur_inc;
	}
}

void	wall_projection(t_glob *glob)
{
	int		i;
	float	wall_height;
	float	dis_proj_plane;

	i = glob->num_rays - 1;
	dis_proj_plane = ((float)WIDTH / 2) / tanf(glob->rays_angle / 2);
	while (i >= 0)
	{
		wall_height = BLOCK_ZIZE / glob->ray[i].ray_long \
		* dis_proj_plane;
		draw_wall(glob, wall_height, glob->ray[i]);
		i--;
	}
}

void	take_the_vertical_distance(t_glob *glob, t_vars *vars, int i)
{
	glob->ray[i].ray_long = vars->vert_dist * \
	cosf(glob->ray[i].ray_angle - glob->vue_angle);
	glob->ray[i].first_hit = '2';
	glob->ray[i].is_door = check_door(glob, glob->ray[i].vert_intercept_x, \
									glob->ray[i].vert_intercept_y);
	if (glob->ray[i].is_door == 0)
		glob->ray[i].is_door = check_door(glob, glob->ray[i].\
		vert_intercept_x - 1, glob->ray[i].vert_intercept_y);
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
		glob->ray[i].is_door = check_door(glob, glob->ray[i].hor_intercept_x, \
									glob->ray[i].hor_intercept_y);
		if (glob->ray[i].is_door == 0)
			glob->ray[i].is_door = check_door(glob, glob->ray[i].\
			hor_intercept_x, glob->ray[i].hor_intercept_y - 1);
	}
	else
		take_the_vertical_distance(glob, &vars, i);
}

void	cast_all_rays(t_glob *glob)
{
	int		i;
	float	new_angle;

	i = 0;
	new_angle = glob->vue_angle + (30 * (M_PI / 180));
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
