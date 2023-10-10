/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:56:56 by lsileoni          #+#    #+#             */
/*   Updated: 2023/10/10 20:26:03 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "graphics.h"
#include <math.h>

static void	pixel_map(t_graphics *graphics, t_loop_vars *l_vars,
		mlx_texture_t *texture, t_ray_vars *r_vars)
{
	l_vars->texture_index_y = l_vars->texture_bound * \
							((double)texture->height / \
							(double)(l_vars->pixels_to_draw));
	mlx_put_pixel(graphics->map->img, l_vars->i, l_vars->j,
		mlx_pixel_get(texture, l_vars->texture_index_x,
			l_vars->texture_index_y, r_vars));
}

static void	paint_pixel(t_ray_vars *r_vars,
		t_graphics *graphics, t_loop_vars *l_vars)
{
	if (r_vars->t_sel == WEST)
		pixel_map(graphics, l_vars, graphics->texture_w, r_vars);
	else if (r_vars->t_sel == NORTH)
		pixel_map(graphics, l_vars, graphics->texture_n, r_vars);
	else if (r_vars->t_sel == SOUTH)
		pixel_map(graphics, l_vars, graphics->texture_s, r_vars);
	else
		pixel_map(graphics, l_vars, graphics->texture_e, r_vars);
}

static int	check_bounds(t_loop_vars *l_vars)
{
	if (l_vars->j < 0)
	{
		l_vars->texture_bound = l_vars->j * -1;
		l_vars->j = 0;
	}
	if (l_vars->j > WINDOW_HEIGHT - 1)
		return (0);
	return (1);
}

static void	init_raycasting(t_graphics *graphics, t_loop_vars *l_vars)
{
	paint_ceiling_floor(graphics);
	l_vars->step_size = ((M_PI / 4.0) / WINDOW_WIDTH);
	l_vars->current_angle = graphics->player->angle - \
							((l_vars->step_size * WINDOW_WIDTH) / 2.0);
}

void	raycasting(t_graphics *graphics)
{
	t_ray_vars	r_vars;
	t_loop_vars	l_vars;

	init_raycasting(graphics, &l_vars);
	l_vars.i = -1;
	while (++l_vars.i < WINDOW_WIDTH)
	{
		reset_current_angle(&l_vars.current_angle);
		set_ray_vars(graphics, l_vars.current_angle, &r_vars);
		l_vars.pixels_to_draw = WINDOW_HEIGHT / r_vars.dist;
		set_texture_x(graphics, &r_vars, &l_vars.texture_index_x);
		l_vars.texture_bound = 0;
		l_vars.j = (WINDOW_HEIGHT / 2) - \
					(l_vars.pixels_to_draw / 2);
		while (l_vars.j < ((WINDOW_HEIGHT / 2) - (l_vars.pixels_to_draw / 2)) + \
				l_vars.pixels_to_draw)
		{
			if (!check_bounds(&l_vars))
				break ;
			paint_pixel(&r_vars, graphics, &l_vars);
			l_vars.texture_bound++;
			l_vars.j++;
		}
		l_vars.current_angle += l_vars.step_size;
	}
}
