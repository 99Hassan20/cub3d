/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_elements_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:36:02 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/25 12:45:00 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	set_color(t_color *color, char *str)
{
	char	**values;

	if (!is_color_str_valid(str))
		error_log("wrong color format");
	values = ft_split(str, ',');
	if (!values)
		return ;
	if (get_2d_arr_size(values) != 3)
	{
		free_2d(values);
		error_log("wrong number of arguments");
	}
	color->red = ft_atoi_v2(values[0]);
	color->green = ft_atoi_v2(values[1]);
	color->blue = ft_atoi_v2(values[2]);
	if (color->green < 0 || color->green > 255
		|| color->red < 0 || color->red > 255
		|| color->blue < 0 || color->blue > 255)
	{
		free_2d(values);
		error_log("color: 0->255");
	}
	free_2d(values);
}

void	set_player_dir(char **dir, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_log("texture file does not exist");
	close(fd);
	*dir = path;
}

void	parse_info(t_glob *data)
{
	int	i;

	i = 0;
	while (data->elements[i].type && data->elements[i].value)
	{
		if (ft_strcmp(data->elements[i].type, "F") == 0)
			set_color(&data->floor, data->elements[i].value);
		else if (ft_strcmp(data->elements[i].type, "C") == 0)
			set_color(&data->ceiling, data->elements[i].value);
		else if (ft_strcmp(data->elements[i].type, "SO") == 0
			|| (data->elements[i].type[0] == 'S'))
			set_player_dir(&data->so, data->elements[i].value);
		else if (ft_strcmp(data->elements[i].type, "EA") == 0
			|| (data->elements[i].type[0] == 'E'))
			set_player_dir(&data->ea, data->elements[i].value);
		else if (ft_strcmp(data->elements[i].type, "WE") == 0
			|| (data->elements[i].type[0] == 'W'))
			set_player_dir(&data->we, data->elements[i].value);
		else if (ft_strcmp(data->elements[i].type, "NO") == 0
			|| (data->elements[i].type[0] == 'N'))
			set_player_dir(&data->no, data->elements[i].value);
		i++;
	}
}
