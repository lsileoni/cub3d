/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:29:26 by jofoto            #+#    #+#             */
/*   Updated: 2023/10/01 15:21:00 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../MLX42/include/MLX42/MLX42.h"
#include "../../includes/graphics.h"

static void change_player_pos(t_graphics *g, double y, double x)
{
	t_player *player;
	int 	**grid;

	grid = g->map->grid;
	player = g->player;
	player->position.y += y;
	if (grid[(int)(player->position.y/BLOCK_SIZE)][(int)(player->position.x/BLOCK_SIZE)] == 1)
		player->position.y -= y;
	player->position.x += x;
	if (grid[(int)(player->position.y/BLOCK_SIZE)][(int)(player->position.x/BLOCK_SIZE)] == 1)
		player->position.x -= x;
}

static void	key_press(void *dt)
{
	t_graphics	*graphics;

	graphics = dt;
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(graphics->mlx);
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_W))
		change_player_pos(graphics, sin(graphics->player->angle) * 2.0 * (graphics->mlx->delta_time * BLOCK_SIZE),
					cos(graphics->player->angle) * 2.0 * (graphics->mlx->delta_time * BLOCK_SIZE));
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_S))
		change_player_pos(graphics, -(sin(graphics->player->angle) * 2.0 * (graphics->mlx->delta_time * BLOCK_SIZE)),
					-(cos(graphics->player->angle) * 2.0 * (graphics->mlx->delta_time * BLOCK_SIZE)));
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_A))
		change_player_pos(graphics, -(sin(graphics->player->angle + M_PI_2) * 2.0 * (graphics->mlx->delta_time * BLOCK_SIZE)),
				-(cos(graphics->player->angle + M_PI_2) * 2.0 * (graphics->mlx->delta_time * BLOCK_SIZE)));
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_D))
		change_player_pos(graphics, sin(graphics->player->angle + M_PI_2) * 2.0 * (graphics->mlx->delta_time * BLOCK_SIZE),
				cos(graphics->player->angle + M_PI_2) * 2.0 * (graphics->mlx->delta_time * BLOCK_SIZE));
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_RIGHT))
		graphics->player->angle += (0.025 * graphics->mlx->delta_time * BLOCK_SIZE);
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_LEFT))
		graphics->player->angle -= (0.025 * graphics->mlx->delta_time * BLOCK_SIZE);
	if (graphics->player->angle > M_PI * 2)
		graphics->player->angle = 0;
	else if (graphics->player->angle < 0)
		graphics->player->angle = M_PI * 2;
}

static void	cursor_func(double xpos, double ypos, void *dt)
{
	t_graphics	*graphics;

	graphics = dt;
	graphics->player->angle += ((xpos - WINDOW_WIDTH/2.0) * MOUSE_SENSITIVITY) * (graphics->mlx->delta_time * BLOCK_SIZE);
	if (graphics->player->angle > M_PI * 2)
		graphics->player->angle = 0;
	else if (graphics->player->angle < 0)
		graphics->player->angle = M_PI * 2;
	mlx_set_mouse_pos(graphics->mlx, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
}

static void	render_frame(void *dt)
{
	t_graphics	*graphics;

	graphics = dt;
	ray(graphics);
}

void	start_loop(t_graphics	*graphics)
{
	mlx_loop_hook(graphics->mlx, key_press, graphics);
	mlx_cursor_hook(graphics->mlx, cursor_func, graphics);
	mlx_loop_hook(graphics->mlx, render_frame, graphics);
	mlx_loop(graphics->mlx);
}
