/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:49:19 by aouchaad          #+#    #+#             */
/*   Updated: 2023/10/05 14:03:04 by hoigag           ###   ########.fr       */
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
	static int	i;

	if (mlx_is_key_down(glob->mlx, MLX_KEY_SPACE) && !inside_door_block(glob))
	{
		i++;
		if (i % 2 == 0 && glob->door_closed == 1)
		{
			glob->door_closed = 0;
			i = 0;
		}
		else if (i % 2 != 0 && glob->door_closed == 0)
		{
			glob->door_closed = 1;
			i = 0;
		}
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
	if (mlx_is_mouse_down(glob->mlx, MLX_MOUSE_BUTTON_LEFT))
		animated_gun(glob);
}
