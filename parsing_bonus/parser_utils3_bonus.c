/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:34:49 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/25 12:44:49 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	change_first_occurenc(char **str, char c, char new_c)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == c)
		{
			(*str)[i] = new_c;
			break ;
		}
		i++;
	}
}

int	is_color_str_valid(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == ',' && str[i + 1] != ',') 
			|| (str[i] == ',' && i - 1 >= 0 && str[i - 1] != ','))
			count++;
		i++;
	}
	return (count == 2);
}
