/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:29:09 by jofoto            #+#    #+#             */
/*   Updated: 2023/09/06 22:44:59 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <math.h>

/*int main(void)
{
  float x;
  float y;
  float x1, y1;
  float x2, y2, dx, dy, step;
  int i, gd = 0, gm;
  
  std::cout << "Enter the value of x1 and y1: ";
  std::cin >> x1 >> y1;
  std::cout << "Enter the value of x2 and y2: ";
  std::cin >> x2 >> y2;
  
  dx = (x2 - x1);
  dy = (y2 - y1);
  if (abs(dx) >= abs(dy))
    step = abs(dx);
  else
    step = abs(dy);
  dx = dx / step;
  dy = dy / step;
  x = x1;
  y = y1;
  i = 0;
  while (i <= step) {
    x = x + dx;
    y = y + dy;
    i = i + 1;
  }
}*/

typedef struct s_ray_vars
{
	float			move_ratio; // how much to move in y for one step in x
	float			curr_step;
	int				up;
	int				left;
	int				last_move; // if it was in x or y
	t_point			curr_pos;
	t_point			blockpos;
}					t_ray_vars;

static t_ray_vars	get_ray_vars(t_graphics *graphics, t_player *player, int **map)
{
	t_ray_vars	vars;
	double		x1;
	double		x2;
	double		y1;
	double		y2;
	double		dx;
	double		dy;
	double		ddist_x;
	double		ddist_y;
	double		sidelen_x;
	double		sidelen_y;
	double		x;
	double		y;
	double		step;
	double		x_step;
	double		y_step;
	double		end_distance;
	double		angle_diff;
	int			map_x;
	int			map_y;
	int			x_steps = 0;
	int			y_steps = 0;
	int			itercount = 0;

	x1 = player->position.x / BLOCK_SIZE;
	y1 = player->position.y / BLOCK_SIZE;
	y2 = player->cursory / BLOCK_SIZE;
	x2 = player->cursorx / BLOCK_SIZE;
	printf("Player angle: %f\n", player->angle);
	printf("Left is pi\nRight is 0\nDown is pi/2\nUp is 3PI/2\n");
	if (player->angle > 0.0 && player->angle <= M_PI / 2.0)
	{
		printf("Looking bottom right\nAngle diff: %f\n", player->angle);
		angle_diff = player->angle;
	}
	else if (player->angle > M_PI / 2.0 && player->angle <= M_PI)
	{
		printf("Looking bottom left\nAngle diff: %f\n", fabs(player->angle - M_PI));
		angle_diff = fabs(player->angle - M_PI);
	}
	else if (player->angle > M_PI && player->angle <= (3.0 * M_PI) / 2.0)
	{
		printf("Looking up left\nAngle diff: %f\n", fabs(player->angle - M_PI));
		angle_diff = fabs(player->angle - M_PI);
	}
	else
	{
		printf("Looking up right\nAngle diff: %f\n", fabs(player->angle - (M_PI * 2.0)));
		angle_diff = fabs(player->angle - (M_PI * 2.0));
	}
	// printf("x2: %f\ty2: %f\n", x2, y2);
	// if (player->angle >= 0.0 && player->angle <= M_PI)
	// 	y2 = 9.0 - y1;
	// else
	// 	y2 = y1;
	// if (player->angle <= ((3.0 * M_PI) / 2.0) && player->angle >= (M_PI / 2.0))
	// 	x2 = x1;
	// else
	// 	x2 = 9.0 - x1;
	// printf("y1: %f\tx1: %f\ny2: %f\tx2: %f\n", y1, x1, y2, x2);
	/*
	 x1 = 360;
	 y1 = 360;
	 x2 = 460;
	 y2 = 410;

	 dx = (x2 - x1) = 100
	 dy = (y2 - y1) = 50 
	 step = 100

	 dx = dx / step = 1
	 dy = dy / step = 0.5
	 */
	dx = (x2 - x1);
	dy = (y2 - y1);
	if (dx == 0)
		x_step = 1e30;
	else
		x_step = sqrt(1 + ((dy / dx) * (dy / dx)));
	if (dy == 0)
		y_step = 1e30;
	else
		y_step = sqrt(1 + ((dx / dy) * (dx / dy)));
	map_x = (int)x1;
	map_y = (int)y1;
	// printf("map_x: %d\tmap_y: %d\n", map_x, map_y);
	if (dx < 0)
	{
		x = -1;
		sidelen_x = (x1 - (double)map_x) * x_step;
	}
	else
	{
		x = 1;
		sidelen_x = (((double)(map_x + 1.0)) - x1) * x_step;
	}
	if (dy < 0)
	{
		y = -1;
		sidelen_y = (y1 - (double)map_y) * y_step;
	}
	else
	{
		y = 1;
		sidelen_y = (((double)(map_y + 1.0)) - y1) * y_step;
	}
	// x = x1;
	// y = y1;
	// printf("dx: %f\tdy: %f\n", dx, dy);
	vars.curr_pos.x = x1;
	vars.curr_pos.y = y1;
	while (1)
	{
		if (sidelen_x < sidelen_y)
		{
			end_distance = sidelen_x;
			sidelen_x += x_step;
			map_x += x;
			vars.last_move = 1;
		}
		else
		{
			end_distance = sidelen_y;
			sidelen_y += y_step;
			map_y += y;
			vars.last_move = 2;
		}
		// printf("x: %d\ty: %d\n", map_x, map_y);
		if (map[map_y][map_x] == 1)
			break ;
		itercount++;
	}
	double opp = 0;
	double adj = 0;
	if (vars.last_move == 1)
	{
		if (x < 0)
			adj = fabs(x1 - (map_x + 1.0));
		else
			adj = fabs(map_x - x1);
		opp = adj * tan(angle_diff);
	}
	else
	{
		if (y < 0)
			adj = fabs(y1 + (map_y + 1.0));
		else
			adj = fabs(map_y - y1);
		opp = adj * tan(angle_diff);
	}
	printf("Adj: %f\tOpp: %f\n", adj, opp);
	vars.curr_pos.y = adj;
	vars.curr_pos.x = opp;
	vars.curr_pos.y *= BLOCK_SIZE;
	vars.curr_pos.x *= BLOCK_SIZE;
	return (vars);
}

void	find_wall_hit(t_ray_vars *vars, double angle, int	**map)
{
	float		x1;
	float		x2;
	float		y1;
	float		y2;
	float		dx;
	float		dy;
	float		step;

	while(map[(int)vars->curr_pos.y][(int)vars->curr_pos.x] != 1)
	{
		while(vars->curr_step < 1)
		{
			vars->curr_pos.x += vars->left;
			if(map[(int)vars->curr_pos.y][(int)vars->curr_pos.x] == 1)
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

	vars = get_ray_vars(graphics, graphics->player, graphics->map->grid);
	// 
	// find_wall_hit(&vars, graphics->player->angle, graphics->map->grid);
	//printf("wall hit is in x: %i, y: %i, ratio =  %f, left = %i, up = %i\n", \
	vars.curr_pos.x, vars.curr_pos.y, vars.move_ratio, vars.left, vars.up);
	// printf("wall x = %f, wall y = %f\n", vars.curr_pos.x, vars.curr_pos.y);
	// vars.curr_pos.x *= 64;
	// vars.curr_pos.y *= 64;
	// printf("player x: %f\tplayer y: %f", graphics->player->position.x, graphics->player->position.y);
	// printf("player x = %f,player  y = %f\n", graphics->player->position.x, graphics->player->position.y);
	connect_points(graphics->player->img, graphics->player->position, vars.curr_pos, 0xff0000ff);
}
