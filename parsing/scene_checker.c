/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:44:03 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/06 12:13:30 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_file_name_valid(char *file_name)
{
	char	*ext;

	if (!file_name)
		return (0);
	if (ft_strlen(file_name) - 4 <= 0)
		return (0);
	ext = ft_strrchr(file_name, '.');
	if (!ext || ft_strcmp(ext, ".cub") != 0)
		return (0);
	return (1);
}

int	is_element_type_valid(char *element)
{
	char	*valid_elements[6];
	int		i;

	i = 0;
	valid_elements[0] = "NO";
	valid_elements[1] = "SO";
	valid_elements[2] = "WE";
	valid_elements[3] = "EA";
	valid_elements[4] = "F";
	valid_elements[5] = "C";
	while (i < 6)
	{
		if (ft_strcmp(element, valid_elements[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	get_scene_elements(t_glob *data)
{
	char	**pair;
	int		i;

	i = 0;
	while (data->map_info[i])
	{
		change_first_occurenc(&data->map_info[i], ' ', 27);
		pair = ft_split(data->map_info[i], 27);
		if (is_element_type_valid(pair[0]) && pair[1])
		{
			data->elements[i].type = ft_strdup(pair[0]);
			data->elements[i].value = ft_strtrim(pair[1], " \t\n");
		}
		else
		{
			free_2d(pair);
			return (0);
		}
		free_2d(pair);
		i++;
	}
	data->elements[i].type = NULL;
	data->elements[i].value = NULL;
	return (1);
}
