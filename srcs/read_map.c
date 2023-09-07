/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:04:47 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/07 18:27:04 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	get_map_data(t_glob *data)
{
	int		counter;
	char	*line;
	int		fd;

	counter = 0;
	fd = open(data->file_name, O_RDONLY);
	if (fd < 0)
		error_log("the given file doesn't exist");
	while (1)
	{
		line = get_line(fd);
		if (!line)
			break ;
		if (line[0] && counter >= MAP_ELEMENTS)
			data->map_height++;
		if (line[0] && counter < MAP_ELEMENTS)
		{
			data->map_info[counter] = ft_strdup(line);
			counter++;
		}
		free(line);
	}
	data->map_info[counter] = 0;
	close(fd);
}

void	get_map(t_glob *data)
{
	char	*line;
	int		fd;
	int		counter;

	counter = 0;
	fd = open(data->file_name, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		remove_new_line(&line);
		if (is_empty_line(line) && counter >= MAP_ELEMENTS + 1)
			error_log("empty line in the middle of the map");
		if (!is_empty_line(line) && counter >= MAP_ELEMENTS)
			data->map[counter - MAP_ELEMENTS] = ft_strdup(line);
		if (!is_empty_line(line))
			counter++;
		free(line);
	}
	if (counter == 0)
		error_log("empty map file");
	data->map[counter - MAP_ELEMENTS] = NULL;
	close(fd);
}
