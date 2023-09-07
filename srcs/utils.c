/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:13:47 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/07 12:31:32 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	fill_map(t_glob *glob)
{
	glob->map = malloc (sizeof(char *) * 15);
	glob->map[14] = NULL;
	glob->map[0] = "1111111111111111111111111\0";
	glob->map[1] = "1000000000011000000000001\0";
	glob->map[2] = "1000000000110001010000001\0";
	glob->map[3] = "1001000000000010001000001\0";
	glob->map[4] = "111111111011000S011100001\0";
	glob->map[5] = "1000000000110000011101111\0";
	glob->map[6] = "1111011111111101110000001\0";
	glob->map[7] = "1111011111111101110101001\0";
	glob->map[8] = "1100000011010101110000001\0";
	glob->map[9] = "1000000000000000110000001\0";
	glob->map[10] = "1000000000000000110101011\0";
	glob->map[11] = "1100000111010101110001111\0";
	glob->map[12] = "1111011111110100000111111\0";
	glob->map[13] = "1111111111111111111111111\0";
}

void	draw_grid(int colon, int line, int color, t_glob *glob)
{
	int i;
	int j;
	i = 0;
	while (i < glob->height)
	{
		j = 0;
		while (j < glob->width)
		{
			if(i % BLOCK_ZIZE == 0 || j % BLOCK_ZIZE == 0)
				mlx_put_pixel(glob->image, 0.2 * j, 0.2 * i, 0x000000);
			j ++;
		}
		i ++;
	}
}

void	draw_mini_map(t_glob *glob)
{
	draw_sky(glob);
	draw_floor(glob);
	cast_all_rays(glob);
	draw_map(glob);
	put_player(glob);
	end_point(glob, 40, glob->vue_angle);
	draw_line(glob, glob->end_x, glob->end_y, 0xFF000000);
}

void	init_func(t_glob *glob)
{
	int i;
	int j;
	char vue;

	i = 0;
	glob->end_x = 0;
	glob->end_y = 0;
	glob->width = (longest_line(glob)) * BLOCK_ZIZE;
	glob->height = (map_size(glob)) * BLOCK_ZIZE;
	glob->image = NULL;
	glob->mlx = NULL;
	glob->start_x = 0;
	glob->start_y = 0;
	glob->vue_angle = 0;
	glob->rays_angle = 60 * (M_PI / 180);
	glob->angle_incr = (60 * (M_PI / 180)) / glob->width;
	glob->num_rays = glob->width;
	glob->rays_long = malloc (sizeof(float) * glob->width);
	while (glob->map[i])
	{
		j = 0;
		while (glob->map[i][j])
		{
			if (glob->map[i][j] == 'E' || glob->map[i][j] == 'N' || glob->map[i][j] == 'S' || glob->map[i][j] == 'W')
			{
				vue = glob->map[i][j];
				glob->start_x = j;
				glob->start_y = i;
			}
			j++;
		}
		i++;
	} 
	glob->start_x = (float)(glob->start_x * BLOCK_ZIZE) + (BLOCK_ZIZE / 2);
	glob->start_y = (float)(glob->start_y * BLOCK_ZIZE) + (BLOCK_ZIZE / 2);
	wich_vue(vue, glob);
}