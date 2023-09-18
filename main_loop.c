/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:29:26 by jofoto            #+#    #+#             */
/*   Updated: 2023/09/16 18:56:51 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "graphics.h"

static void	key_press(void *dt)
{
	t_graphics	*graphics;
	// t_point		previous_position;

	// previous_position = graphics->player->position;
	graphics = dt;
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(graphics->mlx);
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_W))
	{
		graphics->player->position.y += sin(graphics->player->angle) * 2.0;
		graphics->player->position.x += cos(graphics->player->angle) * 2.0;
	}
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_S))
	{
		graphics->player->position.y -= sin(graphics->player->angle) * 2.0;
		graphics->player->position.x -= cos(graphics->player->angle) * 2.0;
	}
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_A))
	{
		graphics->player->position.y -= sin(graphics->player->angle + M_PI_2) * 2.0;
		graphics->player->position.x -= cos(graphics->player->angle + M_PI_2) * 2.0;
	}
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_D))
	{
		graphics->player->position.y += sin(graphics->player->angle + M_PI_2) * 2.0;
		graphics->player->position.x += cos(graphics->player->angle + M_PI_2) * 2.0;
	}
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_RIGHT))
		graphics->player->angle += 0.0125;
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_LEFT))
		graphics->player->angle -= 0.0125;
	if (graphics->player->angle > M_PI * 2)
		graphics->player->angle = 0;
	else if (graphics->player->angle < 0)
		graphics->player->angle = M_PI * 2;
	// if ((int)(graphics->player->position.x / BLOCK_SIZE) - 0.001 >= graphics->map->info->row_size - 2)
	// 	graphics->player->position.x = (((double)graphics->map->info->row_size) - 1.001) * BLOCK_SIZE;
	// if ((graphics->player->position.x / BLOCK_SIZE) + 0.001 <= 1.0)
	// 	graphics->player->position.x = (1.001) * BLOCK_SIZE;
	// if ((int)(graphics->player->position.y / BLOCK_SIZE) - 0.001 >= graphics->map->info->col_size - 2)
	// 	graphics->player->position.y = (((double)graphics->map->info->col_size) - 1.001) * BLOCK_SIZE;
	// if ((graphics->player->position.y / BLOCK_SIZE) + 0.001 <= 1.0)
	// 	graphics->player->position.y = (1.001) * BLOCK_SIZE;
}

static void	cursor_func(double xpos, double ypos, void *dt)
{
	t_graphics	*graphics;

	graphics = dt;
	graphics->player->angle += ((xpos - WINDOW_WIDTH/2) * MOUSE_SENSITIVITY);
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
