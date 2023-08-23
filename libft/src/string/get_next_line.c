/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:35:37 by lsileoni          #+#    #+#             */
/*   Updated: 2022/11/19 16:33:06 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*get_line(const char *line)
{
	char	*str;
	int		i;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	str = malloc(i + 2);
	if (!str)
		return (NULL);
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
		buf = malloc(BUF_SIZE + 1);
		if (!buf)
			return (NULL);
		rval = read(fd, buf, BUF_SIZE);
		if (!rval)
			*s_fd = -1;
		if (rval == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rval] = '\0';
		if (!rval && !line->len)
		{
			free(line->beg);
			free(buf);
			return (NULL);
		}
		line->beg = ft_strjoin_free(line, buf, rval);
		line->content = line->beg;
	}
	return (line->content);
}

void	skip_next_line(t_line *line)
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
	static t_line	line[12289];
	static int		s_fd = -1;
	char			*ret_line;

	if (fd < 0 || fd > 12288)
		return (NULL);
	line[fd].content = read_to_line(fd, &line[fd], &s_fd);
	if (!line[fd].content)
		return (NULL);
	if (!*line[fd].content)
	{
		free(line[fd].beg);
		ret_line = NULL;
		return (ret_line);
	}
	ret_line = get_line(line[fd].content);
	skip_next_line(&line[fd]);
	if (!ret_line)
		free(line[fd].beg);
	s_fd = fd;
	return (ret_line);
}
