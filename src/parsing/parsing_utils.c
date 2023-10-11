/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:32:48 by jofoto            #+#    #+#             */
/*   Updated: 2023/10/11 14:14:24 by lsileoni         ###   ########.fr       */
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

char	*seek_after_colon(char *line)
{
	int	i;

	i = 0;
	if (line[i] == ',')
		p_free_exit(ERR_PARSE, "Error\nNo color specified.\n");
	while (line[i] != ',')
	{
		if (!line[i])
			p_free_exit(ERR_PARSE, "Error\nNo color specified.\n");
		if (!ft_isdigit(line[i]))
			p_free_exit(ERR_PARSE, "Error\nColor value invalid.\n");
		i++;
	}
	return (&line[i + 1]);
}

int	validate_digit(char *line)
{
	while (*line && *line != '\n')
	{
		if (!ft_isdigit(*line))
			p_free_exit(ERR_PARSE, "Error\nColor value invalid.\n");
		line++;
	}
	return (1);
}
