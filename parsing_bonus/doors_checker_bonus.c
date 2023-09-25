/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_checker_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:58:10 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/25 12:44:36 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	is_valid_door_ajacent(char **map, int i, int j)
{
	if (ft_strchr("NSWE0", map[i][j]))
		return (1);
	return (0);
}

int	is_valid_door(char **map, int i, int j)
{
	int	right;
	int	left;
	int	up;
	int	down;

	right = j + 1;
	left = j - 1;
	up = i - 1;
	down = i + 1;
	return ((map[i][right] == '1' && map[i][left] == '1'
					&& is_valid_door_ajacent(map, down, j)
					&& is_valid_door_ajacent(map, up, j))
					|| (is_valid_door_ajacent(map, i, right)
					&& is_valid_door_ajacent(map, i, left)
					&& map[down][j] == '1' && map[up][j] == '1'));
}

int	check_doors(t_glob *data)
{
	int	i;
	int	j;
	int	valid_doors;
	int	counter;

	i = 0;
	counter = 0;
	valid_doors = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'D')
			{
				counter++;
				if (is_valid_door(data->map, i, j))
					valid_doors++;
			}
			j++;
		}
		i++;
	}
	return (valid_doors == counter);
}
