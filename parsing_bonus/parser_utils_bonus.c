/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:43:33 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/09 18:11:27 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

char	*get_line(int fd)
{
	char	*line;
	char	*new_line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	new_line = ft_strtrim(line, " \t\n");
	if (!new_line)
		return (NULL);
	free(line);
	remove_new_line(&new_line);
	return (new_line);
}

void	remove_new_line(char **line)
{
	int	i;

	i = 0;
	while ((*line)[i] && (*line)[i] != '\n')
		i++;
	if ((*line)[i] == '\n')
		(*line)[i] = '\0';
}

int	is_empty_line(char *line)
{
	char	*new_line;

	new_line = ft_strtrim(line, " \t\n");
	if (!new_line[0])
	{
		free(new_line);
		return (1);
	}
	free(new_line);
	return (0);
}

void	free_2d(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	error_log(char *err)
{
	printf("Error\n");
	printf("%s\n", err);
	exit(1);
}
