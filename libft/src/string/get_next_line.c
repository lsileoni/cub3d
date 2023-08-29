/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:53:03 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/29 06:53:03 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*get_line(const char *line)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
		str = mmu_op(MMU_ALLOC, (i + 1));
	else
		str = mmu_op(MMU_ALLOC, (i + 2));
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*read_to_line(int fd, t_line *line, int *s_fd)
{
	char	*buf;
	int		rval;

	rval = 1;
	while (!ft_strnrchr(line->content, '\n', line->len) && rval)
	{
		buf = mmu_op(MMU_ALLOC, (BUFFER_SIZE + 1));
		rval = read(fd, buf, BUFFER_SIZE);
		if (!rval)
			*s_fd = -1;
		if (rval == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rval] = '\0';
		line->beg = ft_strjoin_free(line, buf, rval);
		line->content = line->beg;
	}
	return (line->content);
}

static void	skip_next_line(t_line *line)
{
	int	i;

	i = 0;
	while (line->content[i] && line->content[i] != '\n')
		i++;
	if (line->content[i])
	{
		line->content += i + 1;
		line->len -= i + 1;
	}
	else
	{
		line->content += i;
		line->len -= i;
	}
}

char	*get_next_line(int fd)
{
	static t_line	line;
	static int		s_fd = -1;
	char			*ret_line;

	if (fd != s_fd)
		line = (t_line){NULL, NULL, 0};
	line.content = read_to_line(fd, &line, &s_fd);
	if (!line.content)
		return (NULL);
	if (!*line.content)
	{
		free(line.beg);
		ret_line = NULL;
		return (ret_line);
	}
	ret_line = get_line(line.content);
	skip_next_line(&line);
	if (!ret_line)
		free(line.beg);
	s_fd = fd;
	return (ret_line);
}
