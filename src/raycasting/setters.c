/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:33:15 by lsileoni          #+#    #+#             */
/*   Updated: 2023/10/08 13:34:52 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../MLX42/include/MLX42/MLX42.h"
#include "../../includes/graphics.h"

void	set_north_west(t_ray_vars *vars, double angle)
{
	if ((angle >= M_PI / 2.0) && angle <= ((3 * M_PI) / 2.0))
		vars->west = 0;
	else
		vars->west = 1;
	if ((angle <= M_PI) && angle >= 0)
		vars->north = 1;
	else
		vars->north = 0;
}

void	set_direction_depth(t_dda_vars *dvars,
		t_ray_vars *vars, double angle)
{
	if (dvars->last_move == 2)
	{
		if (vars->north)
			vars->t_sel = NORTH;
		else
			vars->t_sel = SOUTH;
		vars->depth = cos(angle) * dvars->end_distance + dvars->start.x;
	}
	else
	{
		if (vars->west)
			vars->t_sel = WEST;
		else
			vars->t_sel = EAST;
		vars->depth = sin(angle) * dvars->end_distance + dvars->start.y;
	}
	vars->depth -= floor(vars->depth);
}

void	set_ray_vars(t_graphics *graphics, double angle, t_ray_vars *vars)
{
	t_dda_vars	dvars;
	t_player	*player;
	double		current_angle;

	player = graphics->player;
	dvars.start.x = player->position.x / BLOCK_SIZE;
	dvars.start.y = player->position.y / BLOCK_SIZE;
	set_north_west(vars, angle);
	set_endpoint(graphics, &(dvars.end), dvars.start, angle);
	perform_dda(vars, &dvars, graphics->map->grid);
	current_angle = player->angle - angle;
	set_direction_depth(&dvars, vars, angle);
	reset_current_angle(&current_angle);
	vars->dist = vars->dist * cos(current_angle);
}

void	set_texture_x(t_graphics *graphics,
		t_ray_vars *vars, int *texture_index_x)
{
	if (vars->t_sel == WEST)
		*texture_index_x = vars->depth * graphics->texture_w->width;
	else if (vars->t_sel == NORTH)
		*texture_index_x = vars->depth * graphics->texture_n->width;
	else if (vars->t_sel == SOUTH)
		*texture_index_x = vars->depth * graphics->texture_s->width;
	else
		*texture_index_x = vars->depth * graphics->texture_e->width;
}