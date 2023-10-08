/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:56:56 by lsileoni          #+#    #+#             */
/*   Updated: 2023/10/08 13:35:11 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../MLX42/include/MLX42/MLX42.h"
#include "../../includes/graphics.h"
#include <math.h>

void	pixel_map(t_ray_vars *vars, t_graphics *graphics,
		t_loop_vars *l_vars, mlx_texture_t *texture)
{
	l_vars->texture_index_y = l_vars->test * ((double)texture->height / \
		(double)(l_vars->pixels_to_draw));
	mlx_put_pixel(graphics->map->img, l_vars->i, l_vars->j,
		mlx_pixel_get(texture, l_vars->texture_index_x,
			l_vars->texture_index_y));
}

void	paint_pixel(t_ray_vars *vars, t_graphics *graphics, t_loop_vars *l_vars)
{
	if (vars->t_sel == WEST)
		pixel_map(vars, graphics, l_vars, graphics->texture_w);
	else if (vars->t_sel == NORTH)
		pixel_map(vars, graphics, l_vars, graphics->texture_n);
	else if (vars->t_sel == SOUTH)
		pixel_map(vars, graphics, l_vars, graphics->texture_s);
	else
		pixel_map(vars, graphics, l_vars, graphics->texture_e);
}

int	check_bounds(t_loop_vars *l_vars)
{
	if (l_vars->j < 0)
	{
		l_vars->test = l_vars->j * -1;
		l_vars->j = 0;
	}
	if (l_vars->j > WINDOW_HEIGHT - 1)
		return (0);
	return (1);
}

void	init_raycasting(t_graphics *graphics, t_loop_vars *l_vars)
{
	paint_ceiling_floor(graphics);
	l_vars->step_size = (0.001171875 * (640.0 / WINDOW_WIDTH));
	l_vars->current_angle = graphics->player->angle - \
							((l_vars->step_size * WINDOW_WIDTH) / 2);
}

void	ray(t_graphics *graphics)
{
	t_ray_vars	r_vars;
	t_loop_vars	l_vars;

	init_raycasting(graphics, &l_vars);
	l_vars.i = -1;
	while (++l_vars.i < WINDOW_WIDTH)
	{
		reset_current_angle(&l_vars.current_angle);
		set_ray_vars(graphics, l_vars.current_angle, &r_vars);
		l_vars.pixels_to_draw = (70.0 * WINDOW_HEIGHT) / (r_vars.dist * 64.0);
		set_texture_x(graphics, &r_vars, &l_vars.texture_index_x);
		l_vars.test = 0;
		l_vars.j = (WINDOW_HEIGHT / 2) - \
					(l_vars.pixels_to_draw / 2);
		while (l_vars.j < ((WINDOW_HEIGHT / 2) - (l_vars.pixels_to_draw / 2)) + \
				l_vars.pixels_to_draw)
		{
			if (!check_bounds(&l_vars))
				break ;
			paint_pixel(&r_vars, graphics, &l_vars);
			l_vars.test++;
			l_vars.j++;
		}
		l_vars.current_angle += l_vars.step_size;
	}
}
