/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 13:49:31 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/25 12:44:19 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	check_door(t_glob *glob, float end_x, float end_y)
{
	float	x;
	float	y;

	if (end_x < 0 || end_x >= glob->width || end_y < 0 || end_y >= glob->height)
		return (1);
	x = floor(end_x / BLOCK_ZIZE);
	y = floor(end_y / BLOCK_ZIZE);
	if (y >= glob->map_height)
		return (0);
	if (x >= ft_strlen(glob->map[(int)y]))
		return (0);
	if (glob->map[(int)y][(int)x] == 'D')
		return (1);
	return (0); 
}

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
	if (glob->map[(int)y][(int)x] == '1' || glob->map[(int)y][(int)x] == 'D')
		return (1);
	return (0); 
}
