/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersept.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:42:24 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/07 16:39:29 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static void	look_for_wall_hit(t_glob *glob, t_vars *vars, \
float *wallhitx, float *wallhity)
{
	while (vars->nextx >= 0 && vars->nextx < glob->width \
	&& vars->nexty >= 0 && vars->nexty < glob->height)
	{
		if (is_wall(glob, vars->nextx, vars->nexty - vars->var))
		{
			vars->fouandwall = 1;
			(*wallhitx) = vars->nextx;
			(*wallhity) = vars->nexty;
			break ;
		}
		else
		{
			vars->nextx += vars->xstep;
			vars->nexty += vars->ystep;
		}
	}
}

/*
this function finds the horiz intercection of the casted ray whithe the horiz grid lines
and calculate the distance between the player and the last intersection , if there is no intercection
the function returns INT_MAX
*/

float	horizontal_intercept(t_glob *glob, float ray_angle, \
float *wallhitx, float *wallhity)
{
	t_vars	vars;

	vars.yintercept = floor((glob->start_y / BLOCK_ZIZE)) * BLOCK_ZIZE;
	if (ray_facing_down(ray_angle) == 1)
		vars.yintercept += BLOCK_ZIZE;
	vars.xintercept = glob->start_x + (vars.yintercept - \
	glob->start_y) / tan(ray_angle);
	vars.ystep = BLOCK_ZIZE;
	if (ray_facing_down(ray_angle) == 0)
		vars.ystep *= -1;
	vars.xstep = BLOCK_ZIZE / tan(ray_angle);
	if (ray_facing_right(ray_angle) == 0 && vars.xstep > 0)
		vars.xstep *= -1;
	if (ray_facing_right(ray_angle) == 1 && vars.xstep < 0)
		vars.xstep *= -1;
	vars.nextx = vars.xintercept;
	vars.nexty = vars.yintercept;
	/*substract one pixel to force the hit position to be inside the cell*/
	vars.var = 0;
	if (!ray_facing_down(ray_angle))
		vars.var = 1;
	/*increment xstep and ystep antill i fouand a wall*/
	vars.fouandwall = 0;
	look_for_wall_hit(glob, &vars, wallhitx, wallhity);
	if (vars.fouandwall)
		return (distance(glob->start_x, (*wallhitx), \
		glob->start_y, (*wallhity)));
	return (INT_MAX);
}
