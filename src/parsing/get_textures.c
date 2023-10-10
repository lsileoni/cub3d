/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 09:01:59 by lsileoni          #+#    #+#             */
/*   Updated: 2023/10/10 21:22:59 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static char	*extract_texture(char *line)
{
	line += 2;
	while (*line == ' ')
		line++;
	return (strdup_nl(line));
}

static t_rgb	extract_color(char *line)
{
	t_rgb	ret;

	line++;
	while (*line == ' ')
		line++;
	ret.r = ft_atoi(line);
	line = seek_next_colon(line);
	if (line == NULL)
		p_free_exit(5, "Error\nWrong color format.\n");
	line++;
	ret.g = ft_atoi(line);
	line = seek_next_colon(line);
	if (line == NULL)
		p_free_exit(5, "Error\nWrong color format.\n");
	line++;
	ret.b = ft_atoi(line);
	if (ret.b > 255 || ret.b < 0 || *line == 0 || *line == '\n')
		p_free_exit(5, "Error\nWrong color format.\n");
	ret.filled = 1;
	return (ret);
}

static int	assess_line(char *line, t_gameinfo *info)
{
	if (ft_strncmp("NO ", line, 3) == 0)
		info->north_texture = extract_texture(line);
	else if (ft_strncmp("SO ", line, 3) == 0)
		info->south_texture = extract_texture(line);
	else if (ft_strncmp("WE ", line, 3) == 0)
		info->west_texture = extract_texture(line);
	else if (ft_strncmp("EA ", line, 3) == 0)
		info->east_texture = extract_texture(line);
	else if (ft_strncmp("F ", line, 2) == 0)
		info->floor_color = extract_color(line);
	else if (ft_strncmp("C ", line, 2) == 0)
		info->ceiling_color = extract_color(line);
	else if (*line != '\n')
		return (1);
	return (0);
}

static int	got_textures(t_gameinfo *info)
{
	if (info->ceiling_color.filled && \
		info->floor_color.filled && \
		info->north_texture && \
		info->south_texture && \
		info->east_texture && \
		info->west_texture)
	{
		return (1);
	}
	return (0);
}

int	get_textures(int fd, t_gameinfo *info)
{
	char	*line;

	while (got_textures(info) == 0)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (1);
		if (assess_line(line, info) != 0)
			return (2);
		mmu_op(MMU_FREE, (size_t)line);
	}
	return (0);
}
