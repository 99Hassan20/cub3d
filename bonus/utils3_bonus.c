/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:35:50 by aouchaad          #+#    #+#             */
/*   Updated: 2023/10/05 12:53:46 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	map_size(t_glob *glob)
{
	int	i;

	i = 0;
	while (glob->map[i])
		i++;
	return (i);
}

void	wich_vue(char vue, t_glob *glob)
{
	if (vue == 'W')
		glob->vue_angle = M_PI;
	else if (vue == 'N')
		glob->vue_angle = 3 * M_PI_2;
	else if (vue == 'S')
		glob->vue_angle = M_PI_2;
	else if (vue == 'E')
		glob->vue_angle = 0;
}

void	end_point(t_glob *glob, float ray_long, float angle)
{
	glob->end_x = glob->start_x + (cosf(angle) * ray_long);
	glob->end_y = glob->start_y + (sinf(angle) * ray_long);
}

float	distance(float x1, float x2, float y1, float y2)
{
	return ((sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2))));
}

void	put_player(t_glob *glob)
{
	float	i;
	float	j;

	i = glob->start_x - (BLOCK_ZIZE / 2);
	while (i < glob->start_x + (BLOCK_ZIZE / 2))
	{
		j = glob->start_y - (BLOCK_ZIZE / 2);
		while (j < glob->start_y + (BLOCK_ZIZE / 2))
		{
			if (pow(j - (BLOCK_ZIZE / 2) - (glob->start_y - \
			(BLOCK_ZIZE / 2)), 2) + pow(i - (BLOCK_ZIZE / 2) - \
			(glob->start_x - (BLOCK_ZIZE / 2)), 2) <= pow(16, 2))
				mlx_put_pixel(glob->image, 0.15 * i, 0.15 * j, 0x9900FF);
			j ++;
		}
		i ++;
	}
}
