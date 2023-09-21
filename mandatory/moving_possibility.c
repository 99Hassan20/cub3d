/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_possibility.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:14:07 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/21 18:16:10 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	stay_away_from_wall(t_glob *glob, float player_x, float player_y)
{
	float	i;
	float	j;

	j = player_x / (BLOCK_ZIZE);
	i = player_y / (BLOCK_ZIZE);
	if (glob->map[(int)i][(int)j] == '1')
		return (0);
	if (glob->map[(int)(player_y + 1) / BLOCK_ZIZE][(int)j] == '1' && \
			glob->map[(int)i][(int)(player_x + 1) / BLOCK_ZIZE] == '1')
		return (0);
	if (glob->map[(int)(player_y - 1) / BLOCK_ZIZE][(int)j] == '1' && \
			glob->map[(int)i][(int)(player_x - 1) / BLOCK_ZIZE] == '1')
		return (0);
	if (glob->map[(int)(player_y + 1) / BLOCK_ZIZE][(int)j] == '1' && \
			glob->map[(int)i][(int)(player_x - 1) / BLOCK_ZIZE] == '1')
		return (0);
	if (glob->map[(int)(player_y - 1) / BLOCK_ZIZE][(int)j] == '1' && \
			glob->map[(int)i][(int)(player_x + 1) / BLOCK_ZIZE] == '1')
		return (0);
	return (1);
}

static void	left_right(t_glob *glob, int key, float *player_x, float *player_y)
{
	if (key == MLX_KEY_A)
	{
		(*player_x) -= cosf((glob->vue_angle + \
		(90 * (M_PI / 180)))) * MOVE_SPEED;
		(*player_y) -= sinf((glob->vue_angle + \
		(90 * (M_PI / 180)))) * MOVE_SPEED; 
	}
	else if (key == MLX_KEY_D)
	{
		(*player_x) += cosf((glob->vue_angle + \
		(90 * (M_PI / 180)))) * MOVE_SPEED;
		(*player_y) += sinf((glob->vue_angle + \
		(90 * (M_PI / 180)))) * MOVE_SPEED; 
	}
}

int	can_move(t_glob *glob, int key)
{
	float	player_x;
	float	player_y;

	player_x = glob->start_x;
	player_y = glob->start_y;
	if (key == MLX_KEY_W)
	{
		player_x += cosf(glob->vue_angle) * MOVE_SPEED;
		player_y += sinf(glob->vue_angle) * MOVE_SPEED;
	}
	else if (key == MLX_KEY_S)
	{
		player_x -= cosf(glob->vue_angle) * MOVE_SPEED;
		player_y -= sinf(glob->vue_angle) * MOVE_SPEED;
	}
	left_right(glob, key, &player_x, &player_y);
	if (stay_away_from_wall(glob, player_x, player_y) == 0)
		return (0);
	return (1);
}
