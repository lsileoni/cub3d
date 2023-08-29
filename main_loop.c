/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:29:26 by jofoto            #+#    #+#             */
/*   Updated: 2023/08/29 10:00:35 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	key_press(void *dt)
{
	t_graphics	*graphics;

	graphics = dt;
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(graphics->mlx);
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_W))
	{
		graphics->player->img->instances[0].y += round(sin(graphics->player->angle) * 5);
		graphics->player->img->instances[0].x += round(cos(graphics->player->angle) * 5);
	}
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_S))
	{
		graphics->player->img->instances[0].y -= round(sin(graphics->player->angle) * 5);
		graphics->player->img->instances[0].x -= round(cos(graphics->player->angle) * 5);
	}
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_A))
	{
		graphics->player->img->instances[0].y -= round(sin(graphics->player->angle + M_PI_2) * 5);
		graphics->player->img->instances[0].x -= round(cos(graphics->player->angle + M_PI_2) * 5);
	}
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_D))
	{
		graphics->player->img->instances[0].y += round(sin(graphics->player->angle + M_PI_2) * 5);
		graphics->player->img->instances[0].x += round(cos(graphics->player->angle + M_PI_2) * 5);
	}
}

static void	cursor_func(double xpos, double ypos, void *dt)
{
	t_graphics	*graphics;

	graphics = dt;
	graphics->player->angle += (xpos * MOUSE_SENSITIVITY);
	if (graphics->player->angle > M_PI * 2)
		graphics->player->angle = 0;
	else if (graphics->player->angle < 0)
		graphics->player->angle = M_PI * 2;
	mlx_set_mouse_pos(graphics->mlx, 0, 0);
}

static void	render_frame(void *dt)
{
	t_graphics	*graphics;

	graphics = dt;
	draw_player(graphics->player);
}

void	start_loop(t_graphics	*graphics)
{
	mlx_loop_hook(graphics->mlx, key_press, graphics);
	mlx_cursor_hook(graphics->mlx, cursor_func, graphics);
	mlx_loop_hook(graphics->mlx, render_frame, graphics);
	mlx_loop(graphics->mlx);
}
