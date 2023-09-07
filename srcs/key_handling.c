/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:29:22 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/07 12:32:49 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void key_handler(void *param)
{
	t_glob *glob;

	glob = param;
	normalize_angle(&(glob->vue_angle));
	if (mlx_is_key_down(glob->mlx, MLX_KEY_LEFT))
			glob->vue_angle += ROTATION_SPEED;
	if (mlx_is_key_down(glob->mlx, MLX_KEY_RIGHT))
		glob->vue_angle -= ROTATION_SPEED;
	if (mlx_is_key_down(glob->mlx, MLX_KEY_UP))
	{
		if (can_move(glob, MLX_KEY_UP))
		{
			glob->start_x += cos(glob->vue_angle) * MOVE_SPEED;
			glob->start_y += sin(glob->vue_angle) * MOVE_SPEED;
		}
	}
	if (mlx_is_key_down(glob->mlx, MLX_KEY_DOWN))
	{
		if (can_move(glob, MLX_KEY_DOWN))
		{
			glob->start_x -= cos(glob->vue_angle) * MOVE_SPEED;
			glob->start_y -= sin(glob->vue_angle) * MOVE_SPEED;
		}
	}
	normalize_angle(&(glob->vue_angle));
	mlx_delete_image(glob->mlx, glob->image);
	glob->image = mlx_new_image(glob->mlx, glob->width, glob->height);
	mlx_image_to_window(glob->mlx, glob->image, 0, 0);
	draw_mini_map(glob);
}