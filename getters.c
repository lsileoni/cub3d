/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 09:01:59 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/28 11:33:05 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_row_size(char	*map_name)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	i = 0;
	while (line[i])
		i++;
	return (i - 1);
}

int	get_col_size(char *map_name)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(map_name, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		ft_printf("line: %s", line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (i);
}
