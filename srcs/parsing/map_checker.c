/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:19:55 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/07 18:54:23 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	check_surroundings(t_glob *data, int i, int j)
{
	int	left;
	int	right;
	int	up;
	int	down;
	int	error;

	error = 0;
	left = j - 1;
	right = j + 1;
	up = i - 1;
	down = i + 1;
	if (left < 0 || up < 0
		|| right >= (int)ft_strlen(data->map[i])
		|| down >= data->map_height)
		return (0);
	if (j >= (int)ft_strlen(data->map[up])
		|| j >= (int)ft_strlen(data->map[down]))
		return (0);
	if (data->map[i][right] == ' '
		|| data->map[i][left] == ' '
		|| data->map[up][j] == ' '
		|| data->map[down][j] == ' ')
		return (0);
	return (1);
}

int	map_has_walls(t_glob *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if ((data->map[i][j] == '0'
				|| ft_strchr("NSEW", data->map[i][j]))
				&& !check_surroundings(data, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	has_valid_components(t_glob *data)
{
	int	i;
	int	j;
	int	counter;

	i = 0;
	counter = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (!ft_strchr("01NSEW ", data->map[i][j]))
				return (0);
			if (ft_strchr("NSEW", data->map[i][j]))
				counter++;
			j++;
		}
		i++;
	}
	if (counter != 1)
		return (0);
	return (1);
}

void	is_map_valid(t_glob *data)
{
	if (!map_has_walls(data))
		error_log("unclosed wall or space in map");
	if (!has_valid_components(data))
		error_log("invalid map component");
}
