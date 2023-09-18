/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:52:43 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/18 13:08:07 by aouchaad         ###   ########.fr       */
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
		glob->vue_angle = 0;
	else if (vue == 'N')
		glob->vue_angle = M_PI_2;
	else if (vue == 'S')
		glob->vue_angle = (3 * M_PI_2);
	else if (vue == 'E')
		glob->vue_angle = M_PI;
}

float	distance(float x1, float x2, float y1, float y2)
{
	return ((sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2))));
}
