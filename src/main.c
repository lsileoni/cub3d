/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:32:08 by jofoto            #+#    #+#             */
/*   Updated: 2023/09/22 15:36:34 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/graphics.h"

void	print_info(t_gameinfo info)
{
	ft_printf("info.north: %s\n", info.north_texture);
	ft_printf("info.south: %s\n", info.south_texture);
	ft_printf("info.east: %s\n", info.east_texture);
	ft_printf("info.west: %s\n", info.west_texture);
	ft_printf("Ceiling rgb: r: %i, g: %i, b: %i\n", info.ceiling_color.r, info.ceiling_color.g, info.ceiling_color.b);
	ft_printf("Floor rgb: r: %i, g: %i, b: %i\n", info.floor_color.r, info.floor_color.g, info.floor_color.b);
}

void	p_free_exit(int err_no, char *str_to_print)
{
	ft_printf("%s", str_to_print);
	mmu_op(MMU_DESTROY, 0);
	exit (err_no);
}

int	main(int argc, char **argv)
{
	t_gameinfo	info;
	t_graphics	graphics;

	mmu_op(MMU_CREATE, 0);
	if (argc < 2)
	{
		ft_printf("Too few arguments!\n");
		return (1);
	}
	init_info(argv[1], &info);
	print_info(info);
	/* info.row_size = get_row_size(argv[1]);
	info.col_size = get_col_size(argv[1]);
	info.grid = mmu_op(MMU_ALLOC, (sizeof(void *) * info.col_size));
	extract_grid(info.grid, argv[1], &info);
	flood_fill(info.grid, info);
	if (!check_validity(info.grid, info))
	{
		ft_printf("Invalid map!\n");
		return (2);
	}
	restore_grid(info.grid, info);
	print_grid(info.grid, info);
	init_graphics(&graphics, info.grid, &info);
	mlx_texture_t* texture = mlx_load_png("./textures/smile.png");
	if(texture == NULL)
	{
		printf("failed to open texture\n");
		return (3);
	}
	graphics.texture = texture;
	start_loop(&graphics);
	mlx_terminate(graphics.mlx); // put in in the exit functions (ESC, etc.)
	return (0); */
}
