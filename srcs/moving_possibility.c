/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_possibility.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:21:08 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/07 12:32:37 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	stay_away_from_wall(t_glob *glob, float player_x, float player_y)
{
	float	i;
	float	j;

	j = player_x / (BLOCK_ZIZE);
	i = player_y / (BLOCK_ZIZE);
	if (glob->map[(int)i][(int)j] == '1')
		return (0);
	i = (player_y + 3) / BLOCK_ZIZE;
	if (glob->map[(int)i][(int)j] == '1')
		return (0);
	i = (player_y - 3) / BLOCK_ZIZE;
	if (glob->map[(int)i][(int)j] == '1')
		return (0);
	j = (player_x + 3) / BLOCK_ZIZE;
	if (glob->map[(int)i][(int)j] == '1')
		return (0);
	j = (player_x - 3) / BLOCK_ZIZE;
	if (glob->map[(int)i][(int)j] == '1')
		return (0);
	return (1);
}

int	can_move(t_glob *glob, int key)
{
	float	player_x;
	float	player_y;

	player_x = glob->start_x;
	player_y = glob->start_y;
	if (key == MLX_KEY_UP)
	{
		player_x += cos(glob->vue_angle) * MOVE_SPEED;
		player_y += sin(glob->vue_angle) * MOVE_SPEED;
	}
	else if (key == MLX_KEY_DOWN)
	{
		player_x -= cos(glob->vue_angle) * MOVE_SPEED;
		player_y -= sin(glob->vue_angle) * MOVE_SPEED;
	}
	if (stay_away_from_wall(glob, player_x, player_y) == 0)
		return (0);
	return (1);
}
