/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:09:45 by lsileoni          #+#    #+#             */
/*   Updated: 2023/10/08 14:32:20 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../MLX42/include/MLX42/MLX42.h"
#include "../../includes/graphics.h"

static void	change_player_pos(t_graphics *g, double y, double x)
{
	t_player	*player;
	int			**grid;

	grid = g->map->grid;
	player = g->player;
	player->position.y += y;
	if (grid[(int)(player->position.y / BLOCK_SIZE)]
			[(int)(player->position.x / BLOCK_SIZE)] == 1)
		player->position.y -= y;
	player->position.x += x;
	if (grid[(int)(player->position.y / BLOCK_SIZE)]
			[(int)(player->position.x / BLOCK_SIZE)] == 1)
		player->position.x -= x;
}

static void	check_angle_keys(t_graphics *graphics, double *a, double dt)
{
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_RIGHT))
		*a += (0.025 * dt * BLOCK_SIZE);
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_LEFT))
		*a -= (0.025 * dt * BLOCK_SIZE);
	reset_current_angle(a);
}

void	key_press(void *ptr)
{
	t_graphics	*graphics;
	double		a;
	double		dt;

	graphics = ptr;
	dt = graphics->mlx->delta_time;
	a = graphics->player->angle;
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(graphics->mlx);
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_W))
		change_player_pos(graphics, sin(a) * 2.0 * (dt * BLOCK_SIZE),
			cos(a) * 2.0 * (dt * BLOCK_SIZE));
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_S))
		change_player_pos(graphics, -(sin(a) * 2.0 * (dt * BLOCK_SIZE)),
			-(cos(a) * 2.0 * (dt * BLOCK_SIZE)));
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_A))
		change_player_pos(graphics,
			-(sin(a + M_PI_2) * 2.0 * (dt * BLOCK_SIZE)),
			-(cos(a + M_PI_2) * 2.0 * (dt * BLOCK_SIZE)));
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_D))
		change_player_pos(graphics, sin(a + M_PI_2) * 2.0 * (dt * BLOCK_SIZE),
			cos(a + M_PI_2) * 2.0 * (dt * BLOCK_SIZE));
	check_angle_keys(graphics, &a, dt);
}

void	cursor_func(double xpos, double ypos, void *dt)
{
	t_graphics	*graphics;

	graphics = dt;
	graphics->player->angle += ((xpos - WINDOW_WIDTH / 2.0) * \
			MOUSE_SENSITIVITY) * (graphics->mlx->delta_time * BLOCK_SIZE);
	if (graphics->player->angle > M_PI * 2)
		graphics->player->angle = 0;
	else if (graphics->player->angle < 0)
		graphics->player->angle = M_PI * 2;
	mlx_set_mouse_pos(graphics->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void	render_frame(void *dt)
{
	t_graphics	*graphics;

	graphics = dt;
	ray(graphics);
}
