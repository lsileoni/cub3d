/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:48:32 by jofoto            #+#    #+#             */
/*   Updated: 2023/08/29 09:46:17 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	minimap[10][10] = { 
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

void	draw_block(mlx_image_t *map, t_point point0)
{
	int		i;
	t_point	point1;

	i = 0;
	point1.x = point0.x + BLOCK_SIZE;
	point1.y = point0.y;
	while (i < BLOCK_SIZE)
	{
		connect_points(map, point0, point1, 0xFFFFFFFF);
		point1.y++;
		point0.y++;
		i++;
	}
}

void	draw_map(mlx_image_t *map)
{
	int		x;
	int		y;
	t_point	point0;

	y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			if (minimap[y][x] == 1)
			{
				point0.x = x * (BLOCK_SIZE + 1);
				point0.y = y * (BLOCK_SIZE + 1);
				draw_block(map, point0);
			}
			x++;
		}
		y++;
	}
}

void	draw_player(t_player *player)
{
	t_point	point1;

	ft_bzero(player->img->pixels, \
			player->img->width * player->img->height * sizeof(int));
	point1.x = cos(player->angle) * PLAYER_SIZE + WINDOW_WIDTH / 2;
	point1.y = sin(player->angle) * PLAYER_SIZE + WINDOW_HEIGHT / 2;
	connect_points(player->img, player->position, point1, 0xFF0000FF);
}

static void	get_vars(t_point point0, t_point point1, t_conn_pnts_vars *vars)
{
	vars->up = 1;
	vars->left = 1;
	if (point0.y > point1.y)
		vars->up = -1;
	if (point0.x > point1.x)
		vars->left = -1;
	vars->move_ratio = (float)(point0.y - point1.y) / \
						(float)(point0.x - point1.x);
	vars->move_ratio = fabsf(vars->move_ratio);
	vars->curr_step = vars->move_ratio;
	vars->total_steps = abs(point0.x - point1.x) + abs(point0.y - point1.y);
}

void	connect_points(mlx_image_t *img, \
	t_point point0, t_point point1, uint32_t color)
{
	t_conn_pnts_vars	vars;

	get_vars(point0, point1, &vars);
	if (point0.x == point1.x)
	{
		while (point0.y != point1.y)
		{
			mlx_put_pixel(img, point0.x, point0.y, color);
			point0.y += vars.up;
		}
		return ;
	}
	while (point0.x != point1.x)
	{
		while (vars.curr_step >= 1)
		{
			mlx_put_pixel(img, point0.x, point0.y, color);
			vars.curr_step--;
			point0.y += vars.up;
		}
		mlx_put_pixel(img, point0.x, point0.y, color);
		vars.curr_step += vars.move_ratio;
		point0.x += vars.left;
	}
}