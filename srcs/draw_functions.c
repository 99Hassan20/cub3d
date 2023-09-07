/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:11:49 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/07 12:32:24 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
		mlx_put_pixel(glob->image, (0.2 * vars.x_pixel), \
		(0.2 * vars.y_pixel), color);
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
			mlx_put_pixel(glob->image, 0.2 * ((line * BLOCK_ZIZE) + j),
				0.2 * ((colon * BLOCK_ZIZE) + i), color);
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
	while (i < (glob->height / 2))
	{
		j = 0;
		while (j < glob->width)
		{
			mlx_put_pixel(glob->image, j, i, 0x25417896);
			j++;
		}
		i++;
	}
}

void	draw_floor(t_glob *glob)
{
	int	i;
	int	j;

	i = glob->height / 2;
	while (i < glob->height)
	{
		j = 0;
		while (j < glob->width)
		{
			mlx_put_pixel(glob->image, j, i, 0x99774455);
			j++;
		}
		i++;
	}
}

void	draw_map(t_glob *glob)
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
			else
				draw_rect(i, j, 0xD5D6EA, glob);
			j++;
		}
		i++;
	}
}
