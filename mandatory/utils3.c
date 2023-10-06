/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:52:43 by aouchaad          #+#    #+#             */
/*   Updated: 2023/10/05 12:49:42 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

float	distance(float x1, float x2, float y1, float y2)
{
	return ((sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2))));
}
