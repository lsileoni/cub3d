/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:40:48 by jofoto            #+#    #+#             */
/*   Updated: 2023/09/22 16:06:57 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/src/libft.h"

void	init_grid_vec(t_grid_vec *grid_vec)
{
	grid_vec->grid = mmu_op(MMU_ALLOC, sizeof(int *) * 10);
	grid_vec->cols = 0;
	grid_vec->curr_rows = 0;
	grid_vec->row_cap = 10;
}

void	realloc_grid_vec(t_grid_vec	*grid_vec)
{
	
}

void	get_map(int fd, t_gameinfo *info)
{
	t_grid_vec	grid_vec;
	char		*line;

	init_grid_vec(&grid_vec);
	line = get_next_line(fd);
	while (line)
	{
		if (grid_vec.curr_rows == grid_vec.row_cap)
			realloc_grid_vec(&grid_vec)
	}
}
