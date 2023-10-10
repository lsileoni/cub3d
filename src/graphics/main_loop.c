/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:29:26 by jofoto            #+#    #+#             */
/*   Updated: 2023/10/10 20:27:34 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "graphics.h"

void	start_loop(t_graphics	*graphics)
{
	if (!mlx_loop_hook(graphics->mlx, key_press, graphics))
		p_free_exit(11, "Error\nFailed to initialize loop hook\n");
	if (!mlx_loop_hook(graphics->mlx, render_frame, graphics))
		p_free_exit(11, "Error\nFailed to initialize loop hook\n");
	mlx_cursor_hook(graphics->mlx, cursor_func, graphics);
	mlx_loop(graphics->mlx);
}
