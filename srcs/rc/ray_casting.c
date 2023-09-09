/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:53:22 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/09 18:51:52 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

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

void	draw_wall(t_glob *glob, float wall_height, float startx)
{
	float	starty;

	starty = (glob->height / 2) - (wall_height / 2);
	if (starty < 0)
		starty = 0;
	while (starty < (glob->height / 2) + (wall_height / 2))
	{
		if (starty >= glob->height)
			break ;
		mlx_put_pixel(glob->image, (glob->num_rays - (startx + 1)), \
		starty, 0xFFFFFFFF);
		starty++;
	}
}

void	wall_projection(t_glob *glob)
{
	float	i;
	int		wall_height;
	float	dis_proj_plane;

	i = glob->num_rays - 1;
	dis_proj_plane = (glob->width / 2) / tan(glob->rays_angle);
	while (i >= 0)
	{
		wall_height = ((float)BLOCK_ZIZE / (float)glob->rays_long[(int)i]) \
		* dis_proj_plane;
		draw_wall(glob, wall_height, i);
		i--;
	}
}

void	cast_ray(t_glob *glob, float ray_angle, float i)
{
	t_vars	vars;

	vars.horz_dist = horizontal_intercept(glob, ray_angle, \
	&(vars.horiz_iter_x), &(vars.horiz_iter_y));
	vars.vert_dist = vertical_intercept(glob, ray_angle, \
	&(vars.vert_inter_x), &(vars.vert_inter_y));
	if (vars.horz_dist < vars.vert_dist)
		glob->rays_long[(int)i] = vars.horz_dist * \
		cos(ray_angle - glob->vue_angle);
	else
		glob->rays_long[(int)i] = vars.vert_dist * \
		cos(ray_angle - glob->vue_angle);
}

void	cast_all_rays(t_glob *glob)
{
	float	i;
	float	ray_angle;

	i = 0;
	ray_angle = glob->vue_angle + (30 * (M_PI / 180));
	normalize_angle(&ray_angle);
	while (i < glob->num_rays)
	{
		cast_ray(glob, ray_angle, i);
		ray_angle -= glob->angle_incr;
		normalize_angle(&ray_angle);
		i++;
	}
	wall_projection(glob);
}
