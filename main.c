/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:34:11 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/28 09:57:54 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	int			**grid;
	t_gameinfo	info;

	if (argc < 2)
	{
		ft_printf("Too few arguments!\n");
		return (1);
	}
	mmu_op(MMU_CREATE, 0);
	info.row_size = get_row_size(argv[1]);
	info.col_size = get_col_size(argv[1]);
	grid = mmu_op(MMU_ALLOC, (sizeof(void *) * info.col_size));
	extract_grid(grid, argv[1], &info); 
    floodFill(grid, info);
	if (!check_validity(grid, info))
	{
		ft_printf("Invalid map!\n");
		return (1);
	}
	restore_grid(grid, info);
	print_grid(grid, info);
    return (0);
}
