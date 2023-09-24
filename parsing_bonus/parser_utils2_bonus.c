/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:47:29 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/24 13:04:30 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	scene_parser(t_glob *data, char *file, int argc)
{
	if (argc != 2)
		error_log("Usage: ./cub3D {file_name}.cub");
	if (!is_file_name_valid(file))
		error_log("Invalid .cub file");
	data->file_name = file;
	data->map_height = 0;
	data->map_info = malloc(sizeof(char *) * (MAP_ELEMENTS + 1));
	if (!data->map_info)
		return ;
	get_map_data(data);
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		return ;
	get_map(data);
	data->elements = malloc(sizeof(t_element) * 7);
	if (!data->elements)
		return ;
	if (!get_scene_elements(data)
		|| !check_doors(data))
		error_log("Invalid scene elements");
	is_map_valid(data);
	parse_info(data);
}

int	ft_atoi_v2(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			error_log("please provide a digit");
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

int	get_2d_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
