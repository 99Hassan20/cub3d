/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:58:10 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/23 15:59:41 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int is_valid_door(char **map, int i, int j)
{
    return ((map[i][j + 1] == '1' && map[i][j - 1] == '1'
                    && map[i + 1][j] == '0' && map[i - 1][j] == '0')
                    ||(map[i][j + 1] == '0' && map[i][j - 1] == '0'
                    && map[i + 1][j] == '1' && map[i - 1][j] == '1'));
}

int	check_doors(t_glob *data)
{
    int	i;
    int	j;
    int valid_doors;
    int counter;
    
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


