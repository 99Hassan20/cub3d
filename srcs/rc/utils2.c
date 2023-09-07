/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:31:40 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/07 16:39:29 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	longest_line(t_glob *glob)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(glob->map[i]);
	i++;
	while (glob->map[i])
	{
		if (ft_strlen(glob->map[i]) > size)
			size = ft_strlen(glob->map[i]);
		i++;
	}
	return (size);
}

void	normalize_angle(float *angle)
{
	(*angle) = fmod((*angle), (2 * M_PI));
	if ((*angle) <= 0.0)
		(*angle) += (2 * M_PI) + (*angle);
}

int	ray_facing_down(float ray_angle)
{
	if (ray_angle < M_PI && ray_angle > 0)
		return (1);
	return (0);
}

int	ray_facing_right(float ray_angle)
{
	if (ray_angle < (M_PI / 2) || ray_angle > (3 * (M_PI / 2)))
		return (1);
	return (0);
}
