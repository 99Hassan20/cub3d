/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:11:49 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/25 12:43:41 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	draw_line(t_glob *glob, float end_x, float end_y, int color)
{
	t_vars	vars;
	int		i;

	vars.dx = end_x - glob->start_x;
	vars.dy = end_y - glob->start_y;
	if (fabs(vars.dx) > fabs(vars.dy))
		vars.steps = fabs(vars.dx);
	else
		vars.steps = fabs(vars.dy);
	vars.x_inc = vars.dx / vars.steps;
	vars.y_inc = vars.dy / vars.steps;
	i = 0;
	vars.x_pixel = glob->start_x;
	vars.y_pixel = glob->start_y;
	while (i <= vars.steps)
	{
		if (vars.x_pixel >= 0 && vars.x_pixel < glob->width \
		&& vars.y_pixel >= 0 && vars.y_pixel < glob->height) 
			mlx_put_pixel(glob->image, (vars.x_pixel * 0.15), \
			(vars.y_pixel * 0.15), color);
		vars.x_pixel += vars.x_inc;
		vars.y_pixel += vars.y_inc;
		i++;
	}
}

void	draw_rect(int colon, int line, int color, t_glob *glob)
{
	int	i;
	int	j;

	i = 0;
	while (i < BLOCK_ZIZE)
	{
		j = 0;
		while (j < BLOCK_ZIZE)
		{
			mlx_put_pixel(glob->image, 0.15 * ((line * BLOCK_ZIZE) + j),
				0.15 * ((colon * BLOCK_ZIZE) + i), color);
			j++;
		}
		i++;
	}
}

void	draw_sky(t_glob *glob)
{
	int	i;
	int	j;

	i = 0;
	while (i < (HEIGHT / 2)) 
	{
		j = 0;
		while (j < WIDTH) 
		{
			mlx_put_pixel(glob->image, j, i, get_rgba(glob->ceiling.red, \
			glob->ceiling.green, glob->ceiling.blue, 255));
			j++;
		}
		i++;
	}
}

void	draw_floor(t_glob *glob)
{
	int	i;
	int	j;

	i = HEIGHT / 2; 
	while (i < HEIGHT) 
	{
		j = 0;
		while (j < WIDTH) 
		{
			mlx_put_pixel(glob->image, j, i, get_rgba(glob->floor.red, \
			glob->floor.green, glob->floor.blue, 255));
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_glob *glob)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((glob->map)[i])
	{
		j = 0;
		while ((glob->map)[i][j])
		{
			if ((glob->map)[i][j] == '1')
				draw_rect(i, j, 0x838996, glob);
			else if ((glob->map)[i][j] == 'D')
				draw_rect(i, j, 0x124595, glob);
			else if ((glob->map)[i][j] != ' ')
				draw_rect(i, j, 0xD5D6EA, glob);
			j++;
		}
		i++;
	}
}
