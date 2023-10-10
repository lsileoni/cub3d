/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:40:48 by jofoto            #+#    #+#             */
/*   Updated: 2023/10/10 20:26:43 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

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
		info->start_y = col;
		info->start_x = grid_vec->curr_rows;
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
	grid_vec->grid[grid_vec->curr_rows] = mmu_op(MMU_ALLOC, \
											sizeof(int) * len + 1);
	grid_vec->grid[grid_vec->curr_rows][len] = INT_ARR_NULL;
	grid_vec->grid[grid_vec->curr_rows][len - 1] = INT_ARR_NULL;
	while (line[i] && line[i] != '\n')
	{
		assign_grid_element(grid_vec, i, line[i], info);
		i++;
	}
	if (grid_vec->cols < i)
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
			grid[i][j++] = 0;
		i++;
	}
	while (i >= 0)
		mmu_op(MMU_FREE, (size_t)grid_vec->grid[i--]);
	mmu_op(MMU_FREE, (size_t)grid_vec->grid);
	return (grid);
}

static void	check_remainder_of_fd(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && *line == '\n')
	{
		mmu_op(MMU_FREE, (size_t)line);
		line = get_next_line(fd);
	}
	if (line == NULL)
		return ;
	close(fd);
	p_free_exit(5, "Error\nCant have anything after the map!\n");
}

void	get_grid(int fd, t_gameinfo *info)
{
	t_grid_vec	grid_vec;
	char		*line;

	init_grid_vec(&grid_vec);
	line = skip_newlines(fd);
	while (line && *line != '\n')
	{
		if (grid_vec.curr_rows == grid_vec.row_cap)
			grid_vec = realloc_grid_vec(grid_vec);
		assign_line(&grid_vec, line, info);
		grid_vec.curr_rows++;
		mmu_op(MMU_FREE, (size_t)line);
		line = get_next_line(fd);
	}
	if (line)
	{
		mmu_op(MMU_FREE, (size_t)line);
		check_remainder_of_fd(fd);
	}
	close(fd);
	info->grid = format_grid(&grid_vec);
	info->row_size = grid_vec.cols;
	info->col_size = grid_vec.curr_rows;
}
