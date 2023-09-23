/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:40:48 by jofoto            #+#    #+#             */
/*   Updated: 2023/09/23 16:50:57 by jofoto           ###   ########.fr       */
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

t_grid_vec	realloc_grid_vec(t_grid_vec	grid_vec)
{
	t_grid_vec	new_vec;
	int			i;

	new_vec.cols = grid_vec.cols;
	new_vec.curr_rows = grid_vec.curr_rows;
	new_vec.row_cap = grid_vec.row_cap * 2;
	new_vec.grid = mmu_op(MMU_ALLOC, sizeof(int*) * new_vec.row_cap);
	i = 0;
	while (i < grid_vec.row_cap)
	{
		new_vec.grid[i] = grid_vec.grid[i];
		i++;
	}
	mmu_op(MMU_FREE, (size_t)grid_vec.grid);
	return (new_vec);
}
static void	assign_grid_element(t_grid_vec *grid_vec, int col,
								char c, t_gameinfo *info)
{
	if (c == '0' || c == '1')
		grid_vec->grid[grid_vec->curr_rows][col] = c - 48;
	else if (c == ' ')
		grid_vec->grid[grid_vec->curr_rows][col] = 1;
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (info->player_found == 1)
			p_free_exit(6, "Cant have multiple players!\n");
		info->start_x = col;
		info->start_y = grid_vec->curr_rows;
		if (c == 'S')
			info->start_direction = M_PI_2;
		else if (c == 'N')
			info->start_direction = 3 * M_PI_2;
		else if (c == 'W')
			info->start_direction = M_PI;
		else if (c == 'E')
			info->start_direction = 0;
		grid_vec->grid[grid_vec->curr_rows][col] = 0;
		info->player_found = 1;
	}
	else
		p_free_exit(5, "Unknown symbol in grid\n");
}
void	assign_line(t_grid_vec *grid_vec, char *line, t_gameinfo *info)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(line);
	grid_vec->grid[grid_vec->curr_rows] = mmu_op(MMU_ALLOC, sizeof(int) * len + 1);
	grid_vec->grid[grid_vec->curr_rows][len] = INT_ARR_NULL;
	grid_vec->grid[grid_vec->curr_rows][len - 1] = INT_ARR_NULL;
	while(line[i] && line[i] != '\n')
	{
		assign_grid_element(grid_vec, i, line[i], info);
		i++;
	}
	if(grid_vec->cols < i)
		grid_vec->cols = i;
}

int	**format_grid(t_grid_vec *grid_vec)
{
	int	**grid;
	int	i;
	int	j;

	i = 0;
	grid = mmu_op(MMU_ALLOC, sizeof(int *) * grid_vec->curr_rows);
	while (i < grid_vec->curr_rows)
	{
		j = 0;
		grid[i] = mmu_op(MMU_ALLOC, sizeof(int) * grid_vec->cols);
		while (grid_vec->grid[i][j] != INT_ARR_NULL)
		{
			grid[i][j] = grid_vec->grid[i][j];
			j++;
		}
		while (j < grid_vec->cols)
			grid[i][j++] = 1;
		i++;
	}
	while(i >= 0)
		mmu_op(MMU_FREE, (size_t)grid_vec->grid[i--]);
	mmu_op(MMU_FREE, (size_t)grid_vec->grid);
	return (grid);
}

void	get_grid(int fd, t_gameinfo *info)
{
	t_grid_vec	grid_vec;
	char		*line;

	init_grid_vec(&grid_vec);
	line = get_next_line(fd);
	while (line)
	{
		if (grid_vec.curr_rows == grid_vec.row_cap)
			grid_vec = realloc_grid_vec(grid_vec);
		assign_line(&grid_vec, line, info);
		grid_vec.curr_rows++;
		mmu_op(MMU_FREE, (size_t)line);
		line = get_next_line(fd);
	}
	close(fd);
	info->grid = format_grid(&grid_vec);
	info->col_size = grid_vec.cols;
	info->row_size = grid_vec.curr_rows;
}
