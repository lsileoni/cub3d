/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:32:08 by jofoto            #+#    #+#             */
/*   Updated: 2023/10/10 21:37:28 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "graphics.h"

void	p_free_exit(int err_no, char *str_to_print)
{
	ft_printf("%s", str_to_print);
	mmu_op(MMU_DESTROY, 0);
	exit (err_no);
}

void	destroy_textures(t_graphics *graphics)
{
	mlx_delete_texture(graphics->texture_e);
	mlx_delete_texture(graphics->texture_s);
	mlx_delete_texture(graphics->texture_w);
	mlx_delete_texture(graphics->texture_n);
}

int	main(int argc, char **argv)
{
	t_gameinfo	info;
	t_graphics	graphics;

	mmu_op(MMU_CREATE, 0);
	if (argc < 2)
	{
		ft_printf("Error\nToo few arguments\n");
		mmu_op(MMU_DESTROY, 0);
		return (ERR_INIT);
	}
	init_info(argv[1], &info);
	flood_fill(info.grid, info);
	if (!check_validity(info.grid, info))
	{
		ft_printf("Error\nInvalid map\n");
		mmu_op(MMU_DESTROY, 0);
		return (ERR_CHECK);
	}
	restore_grid(info.grid, info);
	init_graphics(&graphics, &info);
	start_loop(&graphics);
	destroy_textures(&graphics);
	mlx_terminate(graphics.mlx);
	return (0);
}
