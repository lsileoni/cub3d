/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:15:54 by lsileoni          #+#    #+#             */
/*   Updated: 2023/10/10 20:58:47 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "graphics.h"

void	reset_current_angle(double *current_angle)
{
	if (*current_angle < 0)
		*current_angle += 2 * M_PI;
	if (*current_angle > 2 * M_PI)
		*current_angle -= 2 * M_PI;
}

unsigned int	rgba_to_int(unsigned char r, unsigned char g,
		unsigned char b, unsigned char a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int	mlx_pixel_get(mlx_texture_t *texture, unsigned int texture_index_x, \
		unsigned int texture_index_y, t_ray_vars *r_vars)
{
	unsigned char	rgba[4];
	size_t			pixel_index;

	if (texture_index_x >= 0 && texture_index_x < texture->width && \
			texture_index_y >= 0 && texture_index_y < texture->height)
	{
		pixel_index = (texture_index_y * texture->width + texture_index_x) * \
						texture->bytes_per_pixel;
		rgba[0] = texture->pixels[pixel_index];
		rgba[1] = texture->pixels[pixel_index + 1];
		rgba[2] = texture->pixels[pixel_index + 2];
		rgba[3] = texture->pixels[pixel_index + 3] / ((r_vars->dist / 2.0) + 1);
	}
	else
		return (0);
	return (rgba_to_int(rgba[0], rgba[1], rgba[2], rgba[3]));
}

void	paint_ceiling_floor(t_graphics *graphics)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			if (j > WINDOW_HEIGHT / 2)
				mlx_put_pixel(graphics->map->img, i, j,
					graphics->ceiling_color - (int)(255 - ((((float)j - \
									(WINDOW_HEIGHT / 2.0)) / \
								(WINDOW_HEIGHT / 2.0)) * 255)));
			else
				mlx_put_pixel(graphics->map->img, i, j,
					graphics->floor_color - (int)(((float)j / \
							(WINDOW_HEIGHT / 2.0)) * 255));
			j++;
		}
		i++;
	}
}
