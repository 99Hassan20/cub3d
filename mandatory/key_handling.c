/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:47:33 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/19 16:52:45 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	up_and_down(t_glob *glob)
{
	if (mlx_is_key_down(glob->mlx, MLX_KEY_W))
	{
		if (can_move(glob, MLX_KEY_W))
		{
			glob->start_x += cosf(glob->vue_angle) * MOVE_SPEED;
			glob->start_y += sinf(glob->vue_angle) * MOVE_SPEED;
		}
	}
	if (mlx_is_key_down(glob->mlx, MLX_KEY_S))
	{
		if (can_move(glob, MLX_KEY_S))
		{
			glob->start_x -= cosf(glob->vue_angle) * MOVE_SPEED;
			glob->start_y -= sinf(glob->vue_angle) * MOVE_SPEED;
		}
	}
}

void	left_and_right(t_glob *glob)
{
	if (mlx_is_key_down(glob->mlx, MLX_KEY_D))
	{
		if (can_move(glob, MLX_KEY_D))
		{
			glob->start_x += cosf((glob->vue_angle + \
			(90 * (M_PI / 180)))) * MOVE_SPEED;
			glob->start_y += sinf((glob->vue_angle + \
			(90 * (M_PI / 180)))) * MOVE_SPEED; 
		}
	}
	if (mlx_is_key_down(glob->mlx, MLX_KEY_A))
	{
		if (can_move(glob, MLX_KEY_A))
		{
			glob->start_x -= cosf((glob->vue_angle + \
			(90 * (M_PI / 180)))) * MOVE_SPEED;
			glob->start_y -= sinf((glob->vue_angle + \
			(90 * (M_PI / 180)))) * MOVE_SPEED; 
		}
	}
}

void	escape_button(t_glob *glob)
{
	if (mlx_is_key_down(glob->mlx, MLX_KEY_ESCAPE))
	{
		mlx_delete_image(glob->mlx, glob->image);
		mlx_close_window(glob->mlx);
		mlx_terminate(glob->mlx);
		free_func(glob);
		exit(0);
	}
}

void	key_handler(void *param)
{
	t_glob	*glob;

	glob = param;
	if (mlx_is_key_down(glob->mlx, MLX_KEY_RIGHT))
		glob->vue_angle += glob->rotation_speed;
	if (mlx_is_key_down(glob->mlx, MLX_KEY_LEFT))
		glob->vue_angle -= glob->rotation_speed;
	up_and_down(glob);
	left_and_right(glob);
	escape_button(glob);
	normalize_angle(&(glob->vue_angle));
	mlx_delete_image(glob->mlx, glob->image);
	glob->image = mlx_new_image(glob->mlx, WIDTH, HEIGHT); 
	draw_map(glob);
}
