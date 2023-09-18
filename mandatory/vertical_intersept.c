/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersept.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:54:36 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/18 13:08:11 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	look_for_wall_hit(t_glob *glob, t_vars *vars, t_ray *ray)
{
	vars->fouandwall = 0;
	while (vars->nextx >= 0 && vars->nextx < glob->width && \
	vars->nexty >= 0 && vars->nexty < glob->height)
	{
		if (is_wall(glob, vars->nextx - vars->var, vars->nexty))
		{
			vars->fouandwall = 1;
			ray->vert_intercept_x = vars->nextx;
			ray->vert_intercept_y = vars->nexty;
			break ;
		}
		else
		{
			vars->nextx += vars->xstep;
			vars->nexty += vars->ystep;
		}
	}
}

float	vertical_intercept(t_glob *glob, t_ray *ray)
{
	t_vars	vars;

	vars.var = 0;
	vars.xintercept = floor((glob->start_x / BLOCK_ZIZE)) * BLOCK_ZIZE;
	if (ray_facing_right(ray->ray_angle))
		vars.xintercept += BLOCK_ZIZE;
	vars.yintercept = (glob->start_y + (vars.xintercept - \
	glob->start_x) * tanf(ray->ray_angle));
	vars.xstep = BLOCK_ZIZE;
	if (!ray_facing_right(ray->ray_angle))
		vars.xstep *= -1;
	vars.ystep = (BLOCK_ZIZE * tanf(ray->ray_angle));
	if (!ray_facing_down(ray->ray_angle) && vars.ystep > 0)
		vars.ystep *= -1;
	if (ray_facing_down(ray->ray_angle) && vars.ystep < 0)
		vars.ystep *= -1;
	if (!ray_facing_right(ray->ray_angle))
		vars.var = 1;
	vars.nextx = vars.xintercept;
	vars.nexty = vars.yintercept;
	look_for_wall_hit(glob, &vars, ray);
	if (vars.fouandwall)
		return (distance(glob->start_x, ray->vert_intercept_x, \
		glob->start_y, ray->vert_intercept_y));
	return (INT_MAX);
}