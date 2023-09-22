/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:29:22 by aouchaad          #+#    #+#             */
/*   Updated: 2023/09/22 15:19:52 by aouchaad         ###   ########.fr       */
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
		mlx_delete_image(glob->mlx, glob->image);
		mlx_close_window(glob->mlx);
		mlx_terminate(glob->mlx);
		free_func(glob);
		exit(0);
	}
}

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
	char *half_path;
	char *path;
	
	half_path = ft_strjoin("textures/pics/gun", ft_itoa(i));
	path = ft_strjoin(half_path, ".png");
	free(half_path);
	return(path);
}

// void draw_frame(t_glob *glob, int index)
// {
// 	char	*path;

// 	path = generate_path(index);
// 	mlx_delete_image(glob->mlx, glob->gun_img);
// 	glob->gun_img = mlx_new_image(glob->mlx, WIDTH, HEIGHT);
// 	put_gun(glob, path);
// 	free(path);
// 	mlx_image_to_window(glob->mlx, glob->gun_img, 0, 0);
// }

void	animated_gun(void *param)
{
	t_glob	*glob;
	// int		j;
	glob = param;
	// while (i <= 52)
	// {
	// 	draw_frame(glob, i + 1);
	// 	usleep(500);
	// 	i++;
	// }
	if (glob->frames == 51)
		glob->frames = 0;
	mlx_delete_image(glob->mlx, glob->gun_img);
	glob->gun_img = mlx_new_image(glob->mlx, WIDTH, HEIGHT);
	put_gun(glob, glob->frames + 1);
	printf("frame %d\n", glob->frames);
	mlx_image_to_window(glob->mlx, glob->gun_img, 0, 0);
	glob->frames++;
	// sleep(1);
	// draw_frame(glob, 20);
	// // sleep(1);
	// draw_frame(glob, 30);
	// // sleep(1);
	// draw_frame(glob, 40);
	
	// glob = param;
	// i = 1;
	// while (i <= 52)
	// {
	// 	j = 0;
	// 	i++;
	// }
}

void	key_handler(void *param)
{
	t_glob	*glob;
	int		mouse_posx;
	int		mouse_posy;

	glob = param;
	mouse_posx = -1;
	mouse_posy = -1;
	if ((glob->frames) == 51)
			glob->frames = 0;
	if (glob->frames > 0) {
		mlx_delete_image(glob->mlx, glob->gun_img);
		glob->gun_img = mlx_new_image(glob->mlx, WIDTH, HEIGHT);
		put_gun(glob, glob->frames + 1);
		printf("FFrame %d\n", glob->frames);
		mlx_image_to_window(glob->mlx, glob->gun_img, 0, 0);
		// usleep(50000);
		glob->frames++;
	}
	mlx_get_mouse_pos(glob->mlx, &mouse_posx, &mouse_posy);
	if (mouse_posx >= 0 && mouse_posy >= 0
		&& mouse_posx <= WIDTH && mouse_posy <= HEIGHT) 
	{
		if (mouse_posx > glob->old_mouse_posx)
			glob->vue_angle += (3 * (M_PI / 180));
		else if (mouse_posx < glob->old_mouse_posx)
			glob->vue_angle -= (3 * (M_PI / 180));
		glob->old_mouse_posx = mouse_posx;
		glob->redraw = 1;
		// glob->vue_angle -= acos((mouse_posx - glob->start_x) / distance(glob->start_x, mouse_posx, glob->start_y, mouse_posy));
	}
	if (mlx_is_key_down(glob->mlx, MLX_KEY_SPACE))
	{
		// mlx_delete_image(glob->mlx, glob->gun_img);
		// glob->gun_img = mlx_new_image(glob->mlx, WIDTH, HEIGHT);
		// put_gun(glob, "textures/pics/gun02.png");
		// mlx_loo
		animated_gun(glob);
		// mlx_loop_hook(glob->mlx, animated_gun, glob);
	}
	if (mlx_is_key_down(glob->mlx, MLX_KEY_Q) && !inside_door_block(glob))
	{
		if (glob->door_closed == 1)
			glob->door_closed = 0;
		else
			glob->door_closed = 1;
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
	up_and_down(glob);
	left_and_right(glob);
	escape_button(glob);
	normalize_angle(&(glob->vue_angle));
	// mlx_delete_image(glob->mlx, glob->image);
	// glob->image = mlx_new_image(glob->mlx, WIDTH, HEIGHT); 
	draw_map(glob);
	
}
