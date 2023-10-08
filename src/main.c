/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:32:08 by jofoto            #+#    #+#             */
/*   Updated: 2023/10/08 14:30:19 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/graphics.h"

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
	flood_fill(info.grid, info);
	if (!check_validity(info.grid, info))
	{
		ft_printf("Invalid map!\n");
		return (2);
	}
	restore_grid(info.grid, info);
	print_grid(info.grid, info);
	init_graphics(&graphics, &info);
	start_loop(&graphics);
	mlx_terminate(graphics.mlx);
	return (0);
}
