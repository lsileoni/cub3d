/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:29:26 by jofoto            #+#    #+#             */
/*   Updated: 2023/09/06 22:01:33 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "graphics.h"

static void	key_press(void *dt)
{
	t_graphics	*graphics;

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
		graphics->player->angle += 0.01;
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_LEFT))
		graphics->player->angle -= 0.01;
	if (graphics->player->angle > M_PI * 2)
		graphics->player->angle = 0;
	else if (graphics->player->angle < 0)
		graphics->player->angle = M_PI * 2;
	//printf("(x, y, angle): (%i, %i, %f)\n",\
	graphics->player->position.x, graphics->player->position.y, graphics->player->angle * 57.2958);
}

static void	cursor_func(double xpos, double ypos, void *dt)
{
	t_graphics	*graphics;

	graphics = dt;
	if (graphics->player->angle > M_PI * 2)
		graphics->player->angle = 0;
	else if (graphics->player->angle < 0)
		graphics->player->angle = M_PI * 2;
	if (xpos > graphics->player->cursorx)
		graphics->player->angle += (xpos * MOUSE_SENSITIVITY);
	else
		graphics->player->angle -= (xpos * MOUSE_SENSITIVITY);
	graphics->player->cursorx = xpos;
	graphics->player->cursory = ypos;
	mlx_set_mouse_pos(graphics->mlx, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
}

static void	render_frame(void *dt)
{
	t_graphics	*graphics;

	graphics = dt;
	// draw_player(graphics->player);
	ray(graphics);
}

void	start_loop(t_graphics	*graphics)
{
	mlx_loop_hook(graphics->mlx, key_press, graphics);
	mlx_cursor_hook(graphics->mlx, cursor_func, graphics);
	mlx_loop_hook(graphics->mlx, render_frame, graphics);
	mlx_loop(graphics->mlx);
}
