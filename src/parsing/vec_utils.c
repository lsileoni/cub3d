/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:01:44 by lsileoni          #+#    #+#             */
/*   Updated: 2023/10/16 08:54:46 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_grid_vec(t_grid_vec *grid_vec)
{
	grid_vec->grid = mmu_op(MMU_ALLOC, sizeof(int *) * 10);
	grid_vec->cols = 0;
	grid_vec->curr_rows = 0;
	grid_vec->row_cap = 10;
}

t_grid_vec	realloc_grid_vec(t_grid_vec	grid_vec)
{
	t_grid_vec	new_vec;
	int			i;

	new_vec.cols = grid_vec.cols;
	new_vec.curr_rows = grid_vec.curr_rows;
	new_vec.row_cap = grid_vec.row_cap * 2;
	new_vec.grid = mmu_op(MMU_ALLOC, sizeof(int *) * new_vec.row_cap);
	i = 0;
	while (i < grid_vec.row_cap)
	{
		new_vec.grid[i] = grid_vec.grid[i];
		i++;
	}
	mmu_op(MMU_FREE, (size_t)grid_vec.grid);
	return (new_vec);
}
