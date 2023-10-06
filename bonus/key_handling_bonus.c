/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:29:22 by aouchaad          #+#    #+#             */
/*   Updated: 2023/10/06 17:28:44 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	up_and_down(t_glob *glob)
{
	if (mlx_is_key_down(glob->mlx, MLX_KEY_W))
	{
		if (can_move(glob, MLX_KEY_W))
		{
			glob->start_x += cosf(glob->vue_angle) * MOVE_SPEED;
			glob->start_y += sinf(glob->vue_angle) * MOVE_SPEED;
			glob->redraw = 1;
		}
	}
	if (mlx_is_key_down(glob->mlx, MLX_KEY_S))
	{
		if (can_move(glob, MLX_KEY_S))
		{
			glob->start_x -= cosf(glob->vue_angle) * MOVE_SPEED;
			glob->start_y -= sinf(glob->vue_angle) * MOVE_SPEED;
			glob->redraw = 1;
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
			glob->redraw = 1;
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
			glob->redraw = 1;
		}
	}
}

void	escape_button(t_glob *glob)
{
	if (mlx_is_key_down(glob->mlx, MLX_KEY_ESCAPE))
	{
		delete_textures(glob);
		mlx_delete_image(glob->mlx, glob->image);
		mlx_delete_image(glob->mlx, glob->gun_img);
		mlx_close_window(glob->mlx);
		mlx_terminate(glob->mlx);
		free_func(glob);
		system("leaks cub3D_bonus");
		exit(0);
	}
}

void	rotation(t_glob *glob, int *mouse_posx, int *mouse_posy)
{
	mlx_get_mouse_pos(glob->mlx, mouse_posx, mouse_posy);
	if ((*mouse_posx) >= 0 && (*mouse_posy) >= 0
		&& (*mouse_posx) <= WIDTH && (*mouse_posy) <= HEIGHT) 
	{
		if ((*mouse_posx) > glob->old_mouse_posx)
			glob->vue_angle += (3 * (M_PI / 180));
		else if ((*mouse_posx) < glob->old_mouse_posx)
			glob->vue_angle -= (3 * (M_PI / 180));
		glob->old_mouse_posx = (*mouse_posx);
		glob->redraw = 1;
	}
	if (mlx_is_key_down(glob->mlx, MLX_KEY_RIGHT))
	{
		glob->vue_angle += glob->rotation_speed;
		glob->redraw = 1;
	}
	if (mlx_is_key_down(glob->mlx, MLX_KEY_LEFT))
	{
		glob->vue_angle -= glob->rotation_speed;
		glob->redraw = 1;
	}
}

void	key_handler(void *param)
{
	t_glob	*glob;
	int		mouse_posx;
	int		mouse_posy;

	glob = param;
	mouse_posx = -1;
	mouse_posy = -1;
	gun_animation(glob);
	open_and_close_door(glob);
	rotation(glob, &mouse_posx, &mouse_posy);
	up_and_down(glob);
	left_and_right(glob);
	escape_button(glob);
	normalize_angle(&(glob->vue_angle));
	draw_map(glob);
}
