/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:29:26 by jofoto            #+#    #+#             */
/*   Updated: 2023/09/30 22:37:47 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../MLX42/include/MLX42/MLX42.h"
#include "../../includes/graphics.h"

static void	key_press(void *dt)
{
	t_graphics	*graphics;
	t_point		new_position;

	graphics = dt;
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(graphics->mlx);
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_W))
	{
		new_position.y = graphics->player->position.y + sin(graphics->player->angle) * 2.0;
		graphics->player->position.y += sin(graphics->player->angle) * 2.0;
		if (graphics->map->grid[(int)(graphics->player->position.y/BLOCK_SIZE)][(int)(graphics->player->position.x/BLOCK_SIZE)] == 1)
			graphics->player->position.y -= sin(graphics->player->angle) * 2.0;
		new_position.x = graphics->player->position.x + cos(graphics->player->angle) * 2.0;
		graphics->player->position.x += cos(graphics->player->angle) * 2.0;
		if (graphics->map->grid[(int)(graphics->player->position.y/BLOCK_SIZE)][(int)(graphics->player->position.x/BLOCK_SIZE)] == 1)
			graphics->player->position.x -= cos(graphics->player->angle) * 2.0;
	}
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_S))
	{
		new_position.y = graphics->player->position.y - sin(graphics->player->angle) * 2.0;
		graphics->player->position.y -= sin(graphics->player->angle) * 2.0;
		if (graphics->map->grid[(int)(graphics->player->position.y/BLOCK_SIZE)][(int)(graphics->player->position.x/BLOCK_SIZE)] == 1)
			graphics->player->position.y += sin(graphics->player->angle) * 2.0;
		new_position.x = graphics->player->position.x - cos(graphics->player->angle) * 2.0;
		graphics->player->position.x -= cos(graphics->player->angle) * 2.0;
		if (graphics->map->grid[(int)(graphics->player->position.y/BLOCK_SIZE)][(int)(graphics->player->position.x/BLOCK_SIZE)] == 1)
			graphics->player->position.x += cos(graphics->player->angle) * 2.0;
	}
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_A))
	{
		new_position.y = graphics->player->position.y - sin(graphics->player->angle + M_PI_2) * 2.0;
		graphics->player->position.y -= sin(graphics->player->angle + M_PI_2) * 2.0;
		if (graphics->map->grid[(int)(graphics->player->position.y/BLOCK_SIZE)][(int)(graphics->player->position.x/BLOCK_SIZE)] == 1)
			graphics->player->position.y += sin(graphics->player->angle + M_PI_2) * 2.0;
		new_position.x = graphics->player->position.x - cos(graphics->player->angle + M_PI_2) * 2.0;
		graphics->player->position.x -= cos(graphics->player->angle + M_PI_2) * 2.0;
		if (graphics->map->grid[(int)(graphics->player->position.y/BLOCK_SIZE)][(int)(graphics->player->position.x/BLOCK_SIZE)] == 1)
			graphics->player->position.x += cos(graphics->player->angle + M_PI_2) * 2.0;
	}
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_D))
	{
		new_position.y = graphics->player->position.y + sin(graphics->player->angle + M_PI_2) * 2.0;
		graphics->player->position.y += sin(graphics->player->angle + M_PI_2) * 2.0;
		if (graphics->map->grid[(int)(graphics->player->position.y/BLOCK_SIZE)][(int)(graphics->player->position.x/BLOCK_SIZE)] == 1)
			graphics->player->position.y -= sin(graphics->player->angle + M_PI_2) * 2.0;
		new_position.x = graphics->player->position.x + cos(graphics->player->angle + M_PI_2) * 2.0;
		graphics->player->position.x += cos(graphics->player->angle + M_PI_2) * 2.0;
		if (graphics->map->grid[(int)(graphics->player->position.y/BLOCK_SIZE)][(int)(graphics->player->position.x/BLOCK_SIZE)] == 1)
			graphics->player->position.x -= cos(graphics->player->angle + M_PI_2) * 2.0;
	}
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_RIGHT))
		graphics->player->angle += 0.025;
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_LEFT))
		graphics->player->angle -= 0.025;
	if (graphics->player->angle > M_PI * 2)
		graphics->player->angle = 0;
	else if (graphics->player->angle < 0)
		graphics->player->angle = M_PI * 2;
}

static void	cursor_func(double xpos, double ypos, void *dt)
{
	t_graphics	*graphics;

	graphics = dt;
	graphics->player->angle += ((xpos - WINDOW_WIDTH/2.0) * MOUSE_SENSITIVITY);
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
