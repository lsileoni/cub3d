/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:29:09 by jofoto            #+#    #+#             */
/*   Updated: 2023/08/31 19:51:32 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

typedef struct s_ray_vars
{
	float			move_ratio; // how much to move in y for one step in x
	float			curr_step;
	int				up;
	int				left;
	int				last_move; // if it was in x or y
	t_point			curr_pos;
}					t_ray_vars;

static t_ray_vars	get_ray_vars(t_player *player)
{
	t_ray_vars	vars;

	if(player->angle != M_PI_2 && player->angle != 3 * M_PI_2)
		vars.move_ratio = fabs(tan(player->angle));
	else
		vars.move_ratio = 1000000;
	vars.curr_pos.x = player->position.x / BLOCK_SIZE;
	vars.curr_pos.y = player->position.y / BLOCK_SIZE;
	vars.up = -1;
	vars.left = -1;
	if (player->angle < M_PI_2 || player->angle > 3 * M_PI_2)
		vars.left = 1;
	if (player->angle < M_PI)
		vars.up = 1;
	//vars.curr_step = vars.move_ratio;
	vars.curr_step = ((float)(player->position.x % BLOCK_SIZE) / BLOCK_SIZE) * vars.move_ratio;
	return (vars);
}

void	find_wall_hit(t_ray_vars *vars, double angle, int	**map)
{
	while(map[vars->curr_pos.y][vars->curr_pos.x] != 1)
	{
		while(vars->curr_step < 1)
		{
			vars->curr_pos.x += vars->left;
			if(map[vars->curr_pos.y][vars->curr_pos.x] == 1)
				return ;
			vars->curr_step += vars->move_ratio;
		}
		vars->curr_pos.y += vars->up;
		vars->curr_step--;
	}
}

void	ray(t_graphics *graphics)
{
	t_ray_vars	vars;

	vars = get_ray_vars(graphics->player);
	
	find_wall_hit(&vars, graphics->player->angle, graphics->map->grid);
	//printf("wall hit is in x: %i, y: %i, ratio =  %f, left = %i, up = %i\n", \
	vars.curr_pos.x, vars.curr_pos.y, vars.move_ratio, vars.left, vars.up);
	printf("wall x = %i, wall y = %i\n", vars.curr_pos.x, vars.curr_pos.y);
	vars.curr_pos.x *= 64;
	vars.curr_pos.y *= 64;
	printf("player x = %i,player  y = %i\n", graphics->player->position.x, graphics->player->position.y);
	connect_points(graphics->player->img, graphics->player->position, vars.curr_pos, 0xff0000ff);
}