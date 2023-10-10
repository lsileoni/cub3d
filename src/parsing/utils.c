/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:32:48 by jofoto            #+#    #+#             */
/*   Updated: 2023/10/10 21:22:02 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

char	*strdup_nl(char *str)
{
	char	*p;
	int		i;

	if (str == NULL)
		return (NULL);
	p = mmu_op(MMU_ALLOC, ft_strlen(str) + 1);
	i = 0;
	while (*str && *str != '\n')
	{
		*p = *str;
		str++;
		p++;
		i++;
	}
	*p = '\0';
	return ((char *)p - i);
}

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

char	*skip_newlines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && *line == '\n')
	{
		mmu_op(MMU_FREE, (size_t)line);
		line = get_next_line(fd);
	}
	return (line);
}

char *seek_next_colon(char *line)
{
	int	i;

	i = 0;
	if (line[i] == ',')
		p_free_exit(6, "Error\nNo color specified.\n");
	while (line[i] && line[i] != ',')
	{
		if (!ft_isdigit(line[i]))
			p_free_exit(6, "Error\nColor value invalid.\n");
		i++;
	}
	return &line[i];
}

