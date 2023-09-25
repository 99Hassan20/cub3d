/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:49:19 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/25 12:44:16 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	inside_door_block(t_glob *glob)
{
	int	i;
	int	j;

	i = glob->start_y / BLOCK_ZIZE;
	j = glob->start_x / BLOCK_ZIZE;
	if (glob->map[i][j] == 'D')
		return (1);
	return (0);
}

char	*generate_path(int i)
{
	char	*half_path;
	char	*path;
	char	*num;

	num = ft_itoa(i);
	half_path = ft_strjoin("textures/pics/gun", num);
	free(num);
	path = ft_strjoin(half_path, ".png");
	free(half_path);
	return (path);
}

void	animated_gun(void *param)
{
	t_glob	*glob;

	glob = param;
	if (glob->frames == 51)
		glob->frames = 0;
	mlx_delete_image(glob->mlx, glob->gun_img);
	glob->gun_img = mlx_new_image(glob->mlx, WIDTH, HEIGHT);
	put_gun(glob, glob->frames + 1);
	mlx_image_to_window(glob->mlx, glob->gun_img, 0, 0);
	glob->frames++;
}

void	open_and_close_door(t_glob *glob)
{
	if (mlx_is_key_down(glob->mlx, MLX_KEY_Q) && !inside_door_block(glob))
	{
		if (glob->door_closed == 1)
			glob->door_closed = 0;
		else
			glob->door_closed = 1;
		glob->redraw = 1;
	}
}

void	gun_animation(t_glob *glob)
{
	if ((glob->frames) == 51)
		glob->frames = 0;
	if (glob->frames > 0)
	{
		mlx_delete_image(glob->mlx, glob->gun_img);
		glob->gun_img = mlx_new_image(glob->mlx, WIDTH, HEIGHT);
		put_gun(glob, glob->frames + 1);
		mlx_image_to_window(glob->mlx, glob->gun_img, 0, 0);
		glob->frames++;
	}
	if (mlx_is_key_down(glob->mlx, MLX_KEY_SPACE))
		animated_gun(glob);
}
