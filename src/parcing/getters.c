/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 09:01:59 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/31 12:43:27 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/src/libft.h"

void	p_free_exit(int err_no, char *str_to_print)
{
	ft_printf("%s", str_to_print);
	mmu_op(MMU_DESTROY, 0);
	exit (err_no);
}

char	*strdup_nl(char *str)
{
	char	*p;
	int		i;

	if(str == NULL)
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
	line = ft_strchr(line, ',');
	if (line == NULL)
		p_free_exit(5, "Error\nWrong color format.\nCorrect form: F 255,100,0\n");
	line++;
	ret.g = ft_atoi(line);
	line = ft_strchr(line, ',');
	if (line == NULL)
		p_free_exit(5, "Error\nWrong color format.\nCorrect form: F 255,100,0\n");
	line++;
	ret.b = ft_atoi(line);
	if (ret.b > 255 || ret.b < 0 || *line == 0 || *line == '\n')
		p_free_exit(5, "Error\nWrong color format.\nCorrect form: F 255,100,0\n");
	ret.filled = 1;
	return (ret);
}

static void	assess_line(char *line, t_gameinfo *info)
{
	if (ft_strncmp("NO ", line, 3) == 0)
		info->north_texture = extract_texture(line);
	else if (ft_strncmp("SO ", line, 3) == 0)
		info->south_texture = extract_texture(line);
	else if (ft_strncmp("WE ", line, 3) == 0)
		info->west_texture = extract_texture(line);
	else if (ft_strncmp("EA ", line, 3) == 0)
		info->east_texture = extract_texture(line);
	else if(ft_strncmp("F ", line, 2) == 0)
		info->floor_color = extract_color(line);
	else if(ft_strncmp("C ", line, 2) == 0)
		info->ceiling_color = extract_color(line);
}

static int got_textures(t_gameinfo *info)
{
	if (info->ceiling_color.filled && 
		info->floor_color.filled &&
		info->north_texture &&
		info->south_texture &&
		info->east_texture &&
		info->west_texture)
	{
		return (1);
	}
	return (0);
}

int	get_textures(int fd, t_gameinfo *info)
{
	char *line;

	while (got_textures(info) == 0)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (1);
		assess_line(line, info);
		mmu_op(MMU_FREE, (size_t)line);
	}
	return (0);
}

int	get_row_size(char	*map_name)
{
	int		fd;
	int		i;
	int		ret;
	char	*line;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd); //leak
	i = 0;
	ret = 0;
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
		mmu_op(MMU_FREE, (size_t)line);
		line = get_next_line(fd);
		i++;
	}
	return (i);
}

//void	get_map_size
