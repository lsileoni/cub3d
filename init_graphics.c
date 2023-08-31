/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:48:25 by jofoto            #+#    #+#             */
/*   Updated: 2023/08/31 12:20:29 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "libft/src/libft.h"

static mlx_image_t	*init_map(mlx_t *mlx)
{
	mlx_image_t	*map;

	map = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!map || mlx_image_to_window(mlx, map, 0, 0) < 0)
	{
		printf("Error opening the image\n");
		mmu_op(MMU_DESTROY, 0);
		exit (1); // handle error
	}
	ft_memset(map->pixels, 0, map->width * map->height * sizeof(int));
	draw_map(map);
	return (map);
}

static mlx_win_cursor_t	*init_cursor(mlx_t *mlx)
{
	mlx_win_cursor_t	*cursor;

	cursor = mlx_create_std_cursor(MLX_CURSOR_ARROW);
	if (cursor == NULL)
		exit(1); //handle error
	mlx_set_cursor(mlx, cursor);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_HIDDEN);
	return (cursor);
}

static t_player	*init_player(mlx_t *mlx)
{
	t_player	*player;

	player = mmu_op(MMU_ALLOC, sizeof(t_player));
	player->img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	//player->img = mlx_new_image(mlx, PLAYER_SIZE * 2, PLAYER_SIZE * 2);
	player->position.x = WINDOW_WIDTH / 2;
	player->position.y = WINDOW_HEIGHT / 2;
	player->angle = 0;
	if (!player->img || mlx_image_to_window(mlx, player->img, 0, 0) < 0)
	{
		printf("Error opening the image\n");
		return (NULL);
	}
	draw_player(player);
	return (player);
}

t_graphics	*init_graphics(void)
{
	t_graphics	*graphics;

	graphics = mmu_op(MMU_ALLOC, sizeof(t_graphics));
	graphics->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, \
							"cub3 me daddy", false);
	graphics->map = init_map(graphics->mlx);
	graphics->player = init_player(graphics->mlx);
	graphics->cursor = init_cursor(graphics->mlx);
	return (graphics);
}
