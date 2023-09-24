/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:26:34 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/21 18:15:34 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_map(t_glob *glob)
{
	if (glob->redraw)
	{
		draw_sky(glob);
		draw_floor(glob);
		cast_all_rays(glob);
		glob->redraw = 0;
	}
}

void	init_player_pos(t_glob *glob, char *vue)
{
	int	i;
	int	j;

	i = 0;
	while (glob->map[i])
	{
		j = 0;
		while (glob->map[i][j])
		{
			if (glob->map[i][j] == 'E' || glob->map[i][j] == 'N' || \
			glob->map[i][j] == 'S' || glob->map[i][j] == 'W')
			{
				(*vue) = glob->map[i][j];
				glob->start_x = j;
				glob->start_y = i;
			}
			j++;
		}
		i++;
	}
}

void	init_func(t_glob *glob)
{
	char	vue;

	glob->width = (longest_line(glob)) * BLOCK_ZIZE;
	glob->height = (map_size(glob)) * BLOCK_ZIZE;
	glob->image = NULL;
	glob->mlx = NULL;
	glob->redraw = 1;
	glob->rays_angle = (float)(60 * (M_PI / 180));
	glob->angle_incr = (float)(60 * (M_PI / 180)) / WIDTH; 
	glob->rotation_speed = (float)(3 * (M_PI / 180));
	glob->num_rays = WIDTH; 
	glob->ray = malloc (sizeof(t_ray) * glob->num_rays);
	init_player_pos(glob, &vue);
	glob->start_x = (glob->start_x * BLOCK_ZIZE) + ((float)BLOCK_ZIZE / 2);
	glob->start_y = (glob->start_y * BLOCK_ZIZE) + ((float)BLOCK_ZIZE / 2);
	wich_vue(vue, glob);
}
