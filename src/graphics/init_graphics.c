/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:48:25 by jofoto            #+#    #+#             */
/*   Updated: 2023/09/16 08:52:09 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/graphics.h"
#include "../../libft/src/libft.h"

static t_map	*init_map(mlx_t *mlx, int **grid, t_gameinfo *info)
{
	t_map		*map;
	mlx_image_t	*image;

	map = mmu_op(MMU_ALLOC, sizeof(t_map));
	image = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!image || mlx_image_to_window(mlx, image, 0, 0) < 0)
	{
		printf("Error opening the image\n");
		mmu_op(MMU_DESTROY, 0);
		exit (1); // handle error
	}
	ft_memset(image->pixels, 0, image->width * image->height * sizeof(int));
	map->img = image;
	map->grid = grid;
	map->info = info;
	map->block_size = 64;
	// draw_map(map);
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

static t_player	*init_player(mlx_t *mlx, t_gameinfo *info)
{
	t_player	*player;

	player = mmu_op(MMU_ALLOC, sizeof(t_player));
	player->img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	player->position.x = (((double)info->start_y) + 0.5) * BLOCK_SIZE;
	player->position.y = (((double)info->start_x) + 0.5) * BLOCK_SIZE;
	player->angle = info->start_direction;
	if (!player->img || mlx_image_to_window(mlx, player->img, 0, 0) < 0)
	{
		printf("Error opening the image\n");
		return (NULL);
	}
	// draw_player(player);
	return (player);
}

void	init_graphics(t_graphics *graphics, int **grid, t_gameinfo *info)
{
	graphics->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, \
							"cub3 me daddy", false);
	graphics->map = init_map(graphics->mlx, grid, info);
	graphics->player = init_player(graphics->mlx, info);
	graphics->cursor = init_cursor(graphics->mlx);
}
