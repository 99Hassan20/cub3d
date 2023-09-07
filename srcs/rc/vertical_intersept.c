/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersept.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:34:46 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/07 16:39:29 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static void	look_for_wall_hit(t_glob *glob, t_vars *vars, \
float *wallhitx, float *wallhity)
{
	while (vars->nextx >= 0 && vars->nextx < glob->width && \
	vars->nexty >= 0 && vars->nexty < glob->height)
	{
		if (is_wall(glob, vars->nextx - vars->var, vars->nexty))
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
this function finds the vertical intercection of the casted ray whithe the vertical grid lines
and calculate the distance between the player and the last intersection , if there is no intercection
the function returns INT_MAX
*/

float	vertical_intercept(t_glob *glob, float ray_angle, \
float *wallhitx, float *wallhity)
{
	t_vars	vars;

	vars.var = 0;
	vars.xintercept = floor((glob->start_x / BLOCK_ZIZE)) * BLOCK_ZIZE;
	if (ray_facing_right(ray_angle))
		vars.xintercept += BLOCK_ZIZE;
	vars.yintercept = glob->start_y + (vars.xintercept - \
	glob->start_x) * tan(ray_angle);
	vars.xstep = BLOCK_ZIZE;
	if (!ray_facing_right(ray_angle))
		vars.xstep *= -1;
	vars.ystep = BLOCK_ZIZE * tan(ray_angle);
	if (!ray_facing_down(ray_angle) && vars.ystep > 0)
		vars.ystep *= -1;
	if (ray_facing_down(ray_angle) && vars.ystep < 0)
		vars.ystep *= -1;
	/*substract one pixel to force the hit position to be inside the cell*/
	if (!ray_facing_right(ray_angle))
		vars.var = 1;
	/*increment xstep and ystep antill i fouand a wall*/
	vars.fouandwall = 0;
	vars.nextx = vars.xintercept;
	vars.nexty = vars.yintercept;
	look_for_wall_hit(glob, &vars, wallhitx, wallhity);
	if (vars.fouandwall)
		return (distance(glob->start_x, (*wallhitx), \
		glob->start_y, (*wallhity)));
	return (INT_MAX);
}