/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 09:00:12 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/28 09:03:42 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	extract_grid(int **grid, char *map_name, t_gameinfo *info)
{
	int		fd;
	int		i;
	int		j;
	char	*line;

	fd = open(map_name, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		grid[i] = malloc(sizeof(int) * info->row_size);
		j = 0;
		while (j < info->row_size)
		{
			if (line[j] == ' ')
				grid[i][j] = 0;
			else if (line[j] == 'N' || line[j] == 'S' || line[j] == 'W' || line[j] == 'E')
			{
				info->start_x = i;
				info->start_y = j;
				grid[i][j] = 0;
			}
			else
				grid[i][j] = line[j] - 48;
			j++;
		}
		free(line);
		line = get_next_line(fd);
		i++;
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
	int i;
	int j;

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
