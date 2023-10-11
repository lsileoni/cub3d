/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:19:41 by lsileoni          #+#    #+#             */
/*   Updated: 2023/10/11 15:27:20 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "graphics.h"

static void	dda_starting_conditions(t_dda_vars *d_vars)
{
	if (d_vars->dx < 0)
	{
		d_vars->x = -1;
		d_vars->sidelen_x = (d_vars->start.x - \
				(double)d_vars->map_x) * d_vars->x_step;
	}
	else
	{
		d_vars->x = 1;
		d_vars->sidelen_x = (((double)(d_vars->map_x + 1.0)) - \
				d_vars->start.x) * d_vars->x_step;
	}
	if (d_vars->dy < 0)
	{
		d_vars->y = -1;
		d_vars->sidelen_y = (d_vars->start.y - \
				(double)d_vars->map_y) * d_vars->y_step;
	}
	else
	{
		d_vars->y = 1;
		d_vars->sidelen_y = (((double)(d_vars->map_y + 1.0)) - \
				d_vars->start.y) * d_vars->y_step;
	}
}

static void	dda_init(t_dda_vars *d_vars)
{
	d_vars->dx = (d_vars->end.x - d_vars->start.x);
	d_vars->dy = (d_vars->end.y - d_vars->start.y);
	if (d_vars->dx == 0)
		d_vars->x_step = 1e30;
	else
		d_vars->x_step = sqrt(1 + ((d_vars->dy / d_vars->dx) * \
					(d_vars->dy / d_vars->dx)));
	if (d_vars->dy == 0)
		d_vars->y_step = 1e30;
	else
		d_vars->y_step = sqrt(1 + ((d_vars->dx / d_vars->dy) * \
					(d_vars->dx / d_vars->dy)));
	d_vars->map_x = (int)d_vars->start.x;
	d_vars->map_y = (int)d_vars->start.y;
	dda_starting_conditions(d_vars);
	d_vars->curr_pos.x = d_vars->start.x;
	d_vars->curr_pos.y = d_vars->start.y;
	d_vars->ray_x = d_vars->start.x;
	d_vars->ray_y = d_vars->start.y;
}

static void	dda_increment(t_dda_vars *d_vars)
{
	if (d_vars->sidelen_x < d_vars->sidelen_y)
	{
		d_vars->end_distance = d_vars->sidelen_x;
		d_vars->sidelen_x += d_vars->x_step;
		d_vars->map_x += d_vars->x;
		d_vars->ray_x += d_vars->x;
		d_vars->last_move = 1;
	}
	else
	{
		d_vars->end_distance = d_vars->sidelen_y;
		d_vars->sidelen_y += d_vars->y_step;
		d_vars->map_y += d_vars->y;
		d_vars->ray_y += d_vars->y;
		d_vars->last_move = 2;
	}
}

void	perform_dda(t_graphics *graphics, t_ray_vars *rvars,
		t_dda_vars *d_vars)
{
	int				**grid;
	const t_point	bounds = {graphics->map->info->row_size, 
		graphics->map->info->col_size};

	grid = graphics->map->grid;
	dda_init(d_vars);
	while (1)
	{
		dda_increment(d_vars);
		if ((int)d_vars->map_x < 0 || d_vars->map_x >= bounds.x || \
				d_vars->map_y < 0 || d_vars->map_y >= bounds.y || \
		grid[d_vars->map_y][d_vars->map_x] == 1)
		{
			d_vars->curr_pos.x = d_vars->map_x * BLOCK_SIZE;
			d_vars->curr_pos.y = d_vars->map_y * BLOCK_SIZE;
			break ;
		}
	}
	rvars->dist = d_vars->end_distance;
}
