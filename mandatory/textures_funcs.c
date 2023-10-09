/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:38:35 by aouchaad          #+#    #+#             */
/*   Updated: 2023/10/09 18:02:14 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

mlx_texture_t	*shoose_texture(t_ray ray, t_glob *glob)
{
	if (ray.first_hit == '2' && (ray.ray_angle < M_PI_2 || \
			ray.ray_angle > (3 * M_PI_2)))
		return (glob->txtrs.ea_texture);
	else if (ray.first_hit == '2' && (ray.ray_angle >= M_PI_2 && \
			ray.ray_angle <= (3 * M_PI_2)))
		return (glob->txtrs.we_texture);
	else if (ray.first_hit == '1' && (ray.ray_angle >= 0 && \
			ray.ray_angle <= M_PI))
		return (glob->txtrs.so_texture);
	return (glob->txtrs.no_texture);
}

int	get_color_from_textrs(int x, int y, mlx_texture_t *texture)
{
	int	i;

	i = (x * 4) + ((y * 4) * texture->width);
	return (texture->pixels[i] << 24 | \
	texture->pixels[i + 1] << 16 | texture->pixels[i + 2] << 8 \
										| texture->pixels[i + 3]);
}

void	creat_textures(t_glob *glob)
{
	glob->txtrs.ea_texture = mlx_load_png(glob->ea);
	glob->txtrs.we_texture = mlx_load_png(glob->we);
	glob->txtrs.so_texture = mlx_load_png(glob->so);
	glob->txtrs.no_texture = mlx_load_png(glob->no);
	if (!glob->txtrs.ea_texture || !glob->txtrs.we_texture || \
		!glob->txtrs.so_texture || !glob->txtrs.no_texture)
	{
		delete_textures(glob);
		free_func(glob);
		error_log("fail to load png file");
	}
}

void	delete_textures(t_glob *glob)
{
	if (glob->txtrs.ea_texture)
		mlx_delete_texture(glob->txtrs.ea_texture);
	if (glob->txtrs.we_texture)
		mlx_delete_texture(glob->txtrs.we_texture);
	if (glob->txtrs.no_texture)
		mlx_delete_texture(glob->txtrs.no_texture);
	if (glob->txtrs.so_texture)
		mlx_delete_texture(glob->txtrs.so_texture);
}
