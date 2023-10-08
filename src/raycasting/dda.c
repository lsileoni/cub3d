/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:19:41 by lsileoni          #+#    #+#             */
/*   Updated: 2023/10/08 13:26:45 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../MLX42/include/MLX42/MLX42.h"
#include "../../includes/graphics.h"

static void	dda_starting_conditions(t_dda_vars *dvars)
{
	if (dvars->dx < 0)
	{
		dvars->x = -1;
		dvars->sidelen_x = (dvars->start.x - \
				(double)dvars->map_x) * dvars->x_step;
	}
	else
	{
		dvars->x = 1;
		dvars->sidelen_x = (((double)(dvars->map_x + 1.0)) - \
				dvars->start.x) * dvars->x_step;
	}
	if (dvars->dy < 0)
	{
		dvars->y = -1;
		dvars->sidelen_y = (dvars->start.y - \
				(double)dvars->map_y) * dvars->y_step;
	}
	else
	{
		dvars->y = 1;
		dvars->sidelen_y = (((double)(dvars->map_y + 1.0)) - \
				dvars->start.y) * dvars->y_step;
	}
}

static void	dda_init(t_dda_vars *dvars)
{
	dvars->dx = (dvars->end.x - dvars->start.x);
	dvars->dy = (dvars->end.y - dvars->start.y);
	if (dvars->dx == 0)
		dvars->x_step = 1e30;
	else
		dvars->x_step = sqrt(1 + ((dvars->dy / dvars->dx) * \
					(dvars->dy / dvars->dx)));
	if (dvars->dy == 0)
		dvars->y_step = 1e30;
	else
		dvars->y_step = sqrt(1 + ((dvars->dx / dvars->dy) * \
					(dvars->dx / dvars->dy)));
	dvars->map_x = (int)dvars->start.x;
	dvars->map_y = (int)dvars->start.y;
	dda_starting_conditions(dvars);
	dvars->curr_pos.x = dvars->start.x;
	dvars->curr_pos.y = dvars->start.y;
	dvars->ray_x = dvars->start.x;
	dvars->ray_y = dvars->start.y;
}

static void	dda_increment(t_dda_vars *dvars)
{
	if (dvars->sidelen_x < dvars->sidelen_y)
	{
		dvars->end_distance = dvars->sidelen_x;
		dvars->sidelen_x += dvars->x_step;
		dvars->map_x += dvars->x;
		dvars->ray_x += dvars->x;
		dvars->last_move = 1;
	}
	else
	{
		dvars->end_distance = dvars->sidelen_y;
		dvars->sidelen_y += dvars->y_step;
		dvars->map_y += dvars->y;
		dvars->ray_y += dvars->y;
		dvars->last_move = 2;
	}
}

void	perform_dda(t_ray_vars *rvars, t_dda_vars *dvars, int **grid)
{
	dda_init(dvars);
	while (1)
	{
		dda_increment(dvars);
		if (grid[dvars->map_y][dvars->map_x] == 1)
		{
			dvars->curr_pos.x = dvars->map_x * BLOCK_SIZE;
			dvars->curr_pos.y = dvars->map_y * BLOCK_SIZE;
			break ;
		}
	}
	rvars->dist = dvars->end_distance;
}
