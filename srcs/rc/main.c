/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:08:56 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/09 19:24:50 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	free_func(t_glob *glob)
{
	int		i;

	i = 0;
	free_2d(glob->map_info);
	free_2d(glob->map);
	while (glob->elements[i].type)
	{
		free(glob->elements[i].type);
		free(glob->elements[i].value);
		i++;
	}
	free(glob->rays_long);
	free(glob->elements);
}

int	main(int ac, char **av)
{
	t_glob	glob;

	scene_parser(&glob, av[1], ac);
	init_func(&glob);
	glob.mlx = mlx_init(glob.width, glob.height, "cub3D", false);
	glob.image = mlx_new_image(glob.mlx, glob.width, glob.height);
	draw_map(&glob);
	mlx_image_to_window(glob.mlx, glob.image, 0, 0);
	mlx_loop_hook(glob.mlx, key_handler, &glob);
	mlx_loop(glob.mlx);
	mlx_terminate(glob.mlx);
	free_func(&glob);
	return (0);
}
