/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:47:33 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/18 14:50:32 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int inside_window_borders(float player_x, float player_y)
{
	if (player_x >= WIDTH || player_x < 0 || player_y >= HEIGHT || player_y < 0)
		return (0);
	return (1);
}

int	can_move(t_glob *glob, int key)
{
	if (key == MLX_KEY_W)
	{
		return (inside_window_borders((glob->start_x + cosf(glob->vue_angle) * MOVE_SPEED)\
		, (glob->start_y + sinf(glob->vue_angle) * MOVE_SPEED)));
	}
	else if (key == MLX_KEY_S)
	{
		return (inside_window_borders((glob->start_x - cosf(glob->vue_angle) * MOVE_SPEED)\
		, (glob->start_y - sinf(glob->vue_angle) * MOVE_SPEED)));
	}
	else if (key == MLX_KEY_D)
	{
		return (inside_window_borders((glob->start_x + cosf((glob->vue_angle + (90 * (M_PI / 180)))) * MOVE_SPEED)\
		, (glob->start_y + sinf((glob->vue_angle + (90 * (M_PI / 180)))) * MOVE_SPEED)));
	}
	else if (key == MLX_KEY_A)
	{
		return (inside_window_borders((glob->start_x - cosf((glob->vue_angle + (90 * (M_PI / 180)))) * MOVE_SPEED)\
		, (glob->start_y + sinf((glob->vue_angle - (90 * (M_PI / 180)))) * MOVE_SPEED)));
	}
	return (1);
}

void	up_and_down(t_glob *glob)
{
	if (mlx_is_key_down(glob->mlx, MLX_KEY_W))
	{
		if (!can_move(glob, MLX_KEY_W))
		{
			glob->start_x += cosf(glob->vue_angle) * MOVE_SPEED;
			glob->start_y += sinf(glob->vue_angle) * MOVE_SPEED;
		}
	}
	if (mlx_is_key_down(glob->mlx, MLX_KEY_S))
	{
		if (!can_move(glob, MLX_KEY_S))
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
		if (!can_move(glob, MLX_KEY_D))
		{
			glob->start_x += cosf((glob->vue_angle + \
			(90 * (M_PI / 180)))) * MOVE_SPEED;
			glob->start_y += sinf((glob->vue_angle + \
			(90 * (M_PI / 180)))) * MOVE_SPEED; 
		}
	}
	if (mlx_is_key_down(glob->mlx, MLX_KEY_A))
	{
		if (!can_move(glob, MLX_KEY_A))
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
///////////////////////////////////////////////////////////////
void	draw_line(t_glob *glob, float end_x, float end_y, int color)
{
	t_vars	vars;
	int		i;

	vars.dx = end_x - glob->start_x;
	vars.dy = end_y - glob->start_y;
	if (fabs(vars.dx) > fabs(vars.dy))
		vars.steps = fabs(vars.dx);
	else
		vars.steps = fabs(vars.dy);
	vars.x_inc = vars.dx / vars.steps;
	vars.y_inc = vars.dy / vars.steps;
	i = 0;
	vars.x_pixel = glob->start_x;
	vars.y_pixel = glob->start_y;
	while (i <= vars.steps)
	{
		if (vars.x_pixel >= 0 && vars.x_pixel < glob->width \
		&& vars.y_pixel >= 0 && vars.y_pixel < glob->height) 
			mlx_put_pixel(glob->image, (vars.x_pixel * 0.15), \
			(vars.y_pixel * 0.15), color);
		vars.x_pixel += vars.x_inc;
		vars.y_pixel += vars.y_inc;
		i++;
	}
}
///////////////////////////////////////////////////////////////
void	draw_minimap(t_glob *glob)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((glob->map)[i])
	{
		j = 0;
		while ((glob->map)[i][j])
		{
			if ((glob->map)[i][j] == '1')
				draw_rect(i, j, 0x838996, glob);
			else if ((glob->map)[i][j] != ' ')
				draw_rect(i, j, 0xD5D6EA, glob);
			j++;
		}
		i++;
	}
}
///////////////////////////////////////////////////////////////
void	end_point(t_glob *glob, float ray_long, float angle)
{
	glob->end_x = glob->start_x + (cosf(angle) * ray_long);
	glob->end_y = glob->start_y + (sinf(angle) * ray_long);
}

void	put_player(t_glob *glob)
{
	float	i;
	float	j;

	i = glob->start_x - (BLOCK_ZIZE / 2);
	while (i < glob->start_x + (BLOCK_ZIZE / 2))
	{
		j = glob->start_y - (BLOCK_ZIZE / 2);
		while (j < glob->start_y + (BLOCK_ZIZE / 2))
		{
			if (pow(j - (BLOCK_ZIZE / 2) - (glob->start_y - \
			(BLOCK_ZIZE / 2)), 2) + pow(i - (BLOCK_ZIZE / 2) - \
			(glob->start_x - (BLOCK_ZIZE / 2)), 2) <= pow(16, 2))
				mlx_put_pixel(glob->image, 0.15 * i, 0.15 * j, 0x9900FF);
			j ++;
		}
		i ++;
	}
}
///////////////////////////////////////////////////////////////
void	draw_rect(int colon, int line, int color, t_glob *glob)
{
	int	i;
	int	j;

	i = 0;
	while (i < BLOCK_ZIZE)
	{
		j = 0;
		while (j < BLOCK_ZIZE)
		{
			mlx_put_pixel(glob->image, 0.15 * ((line * BLOCK_ZIZE) + j),
				0.15 * ((colon * BLOCK_ZIZE) + i), color);
			j++;
		}
		i++;
	}
}
///////////////////////////////////////////////////////////////
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