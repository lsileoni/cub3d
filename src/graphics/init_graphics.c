/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:48:25 by jofoto            #+#    #+#             */
/*   Updated: 2023/10/16 08:58:26 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static t_map	*init_map(mlx_t *mlx, t_gameinfo *info)
{
	t_map		*map;
	mlx_image_t	*image;

	map = mmu_op(MMU_ALLOC, sizeof(t_map));
	image = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!image || mlx_image_to_window(mlx, image, 0, 0) < 0)
	{
		mlx_terminate(mlx);
		p_free_exit(ERR_INIT, "Error\nopening the image\n");
		return (NULL);
	}
	ft_memset(image->pixels, 0, image->width * image->height * sizeof(int));
	map->img = image;
	map->grid = info->grid;
	map->info = info;
	map->block_size = 64;
	return (map);
}

static mlx_win_cursor_t	*init_cursor(mlx_t *mlx)
{
	mlx_win_cursor_t	*cursor;

	cursor = mlx_create_std_cursor(MLX_CURSOR_ARROW);
	if (cursor == NULL)
	{
		mlx_terminate(mlx);
		p_free_exit(ERR_INIT, "Error\nallocating the cursor\n");
		return (NULL);
	}
	mlx_set_cursor(mlx, cursor);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_HIDDEN);
	return (cursor);
}

static t_player	*init_player(t_gameinfo *info)
{
	t_player	*player;

	player = mmu_op(MMU_ALLOC, sizeof(t_player));
	player->position.x = (((double)info->start_y) + 0.5) * BLOCK_SIZE;
	player->position.y = (((double)info->start_x) + 0.5) * BLOCK_SIZE;
	player->angle = info->start_direction;
	return (player);
}

static mlx_texture_t	*open_texture(char *path, mlx_t *mlx)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (texture == NULL)
	{
		mlx_terminate(mlx);
		ft_printf("Error\nFailed to open texture '%s'\n", path);
		p_free_exit(ERR_INIT, "");
		return (NULL);
	}
	mmu_op(MMU_FREE, (size_t)path);
	return (texture);
}

void	init_graphics(t_graphics *graphics, t_gameinfo *info)
{
	graphics->ceiling_color = rgba_to_int(info->ceiling_color.r,
			info->ceiling_color.g, info->ceiling_color.b, 255);
	graphics->floor_color = rgba_to_int(info->floor_color.r,
			info->floor_color.g, info->floor_color.b, 255);
	graphics->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, \
							"cub3D", false);
	if (!graphics->mlx)
		p_free_exit(ERR_INIT, "Error\nFailed to init mlx\n");
	graphics->map = init_map(graphics->mlx, info);
	graphics->player = init_player(info);
	graphics->cursor = init_cursor(graphics->mlx);
	graphics->texture_e = open_texture(info->east_texture, graphics->mlx);
	graphics->texture_n = open_texture(info->north_texture, graphics->mlx);
	graphics->texture_s = open_texture(info->south_texture, graphics->mlx);
	graphics->texture_w = open_texture(info->west_texture, graphics->mlx);
}
