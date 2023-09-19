/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:26:34 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/18 14:46:16 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_map(t_glob *glob)
{
	draw_sky(glob);
	draw_floor(glob);
	cast_all_rays(glob);
	draw_minimap(glob);
	put_player(glob);
	end_point(glob, 30, glob->vue_angle);
	draw_line(glob, glob->end_x, glob->end_y, 0xFF000000);
	mlx_image_to_window(glob->mlx, glob->image, 0, 0);
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

	glob->end_x = 0;
	glob->end_y = 0;
	// glob->old_mouse_posx = -1;
	glob->width = (longest_line(glob)) * BLOCK_ZIZE;
	glob->height = (map_size(glob)) * BLOCK_ZIZE;
	glob->image = NULL;
	glob->mlx = NULL;
	glob->start_x = 0;
	glob->start_y = 0;
	glob->vue_angle = 0;
	glob->rays_angle = (float)(60 * (M_PI / 180));
	glob->angle_incr = (float)(60 * (M_PI / 180)) / WIDTH; 
	glob->rotation_speed = (float)(3 * (M_PI / 180));
	glob->num_rays = WIDTH; 
	// glob->rays_long = malloc (sizeof(float) * glob->width);
	glob->ray = malloc (sizeof(t_ray) * glob->num_rays);
	// creat_texture(glob);
	// glob->ray_intesection = malloc(sizeof(char) * (glob->width + 1));
	// glob->ray_intesection[glob->width] = '\0';
	init_player_pos(glob, &vue);
	glob->start_x = (glob->start_x * BLOCK_ZIZE) + ((float)BLOCK_ZIZE / 2);
	glob->start_y = (glob->start_y * BLOCK_ZIZE) + ((float)BLOCK_ZIZE / 2);
	wich_vue(vue, glob);
}