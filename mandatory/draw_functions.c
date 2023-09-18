/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:42:44 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/18 11:43:33 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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