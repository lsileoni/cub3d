/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 09:00:12 by lsileoni          #+#    #+#             */
/*   Updated: 2023/09/22 14:01:27 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/src/libft.h"

static void	assign_grid_element(int **grid, char *line,
								t_i_point p, t_gameinfo *info)
{
	if (line[p.y] == '0' || line[p.y] == '1')
		grid[p.x][p.y] = line[p.y] - 48;
	else if (line[p.y] == ' ')
		grid[p.x][p.y] = 1;
	else if (line[p.y] == 'N' || line[p.y] == 'S' || \
			line[p.y] == 'W' || line[p.y] == 'E')
	{
		if (info->player_found == 1)
			p_free_exit(6, "Cant have multiple players!\n");
		info->start_x = p.x;
		info->start_y = p.y;
		if (line[p.y] == 'S')
			info->start_direction = M_PI_2;
		else if (line[p.y] == 'N')
			info->start_direction = 3 * M_PI_2;
		else if (line[p.y] == 'W')
			info->start_direction = M_PI;
		else if (line[p.y] == 'E')
			info->start_direction = 0;
		grid[p.x][p.y] = 0;
		info->player_found = 1;
	}
	else
		p_free_exit(5, "Unknown symbol in grid\n");
}

void	extract_grid(int **grid, char *map_name, t_gameinfo *info)
{
	int			fd;
	t_i_point	p;
	char		*line;

	fd = open(map_name, O_RDONLY);
	line = get_next_line(fd);
	p.x = 0;
	while (line)
	{
		grid[p.x] = mmu_op(MMU_ALLOC, (sizeof(int) * info->row_size));
		p.y = 0;
		while (p.y < info->row_size)
		{
			assign_grid_element(grid, line, p, info);
			p.y++;
		}
		mmu_op(MMU_FREE, (size_t)line);
		line = get_next_line(fd);
		p.x++;
	}
}

void	restore_grid(int **grid, t_gameinfo info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info.col_size)
	{
		j = 0;
		while (j < info.row_size)
		{
			if (grid[i][j] == 9)
				grid[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	print_grid(int **grid, t_gameinfo info)
{
	int	i;
	int	j;

	ft_printf("Flood Fill Result:\n");
	i = 0;
	while (i < info.col_size)
	{
		j = 0;
		while (j < info.row_size)
		{
			ft_printf("%d", grid[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

int	check_validity(int **grid, t_gameinfo info)
{
	int	y;
	int	x;

	y = 0;
	while (y < info.col_size)
	{
		x = 0;
		while (x < info.row_size)
		{
			if (grid[y][x] == 9)
			{
				if (x == 0 || x == (info.row_size - 1))
					return (0);
				if (y == 0 || y == (info.col_size - 1))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
