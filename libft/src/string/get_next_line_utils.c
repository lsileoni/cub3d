/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:35:14 by lsileoni          #+#    #+#             */
/*   Updated: 2022/11/19 16:31:35 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnrchr(const char *s, int c, int len)
{
	int	i;

	if (!s)
		return (NULL);
	if (!len)
		i = 0;
	else
		i = len - 1;
	if ((char)c == 0)
		return ((char *)s);
	while (i)
	{
		if (s[i--] == (char)c)
			return ((char *)s);
	}
	return (NULL);
}

static char	*alloc_string(int len)
{
	char	*p;

	p = malloc(len + 1);
	if (!p)
		return (NULL);
	return (p);
}

static void	*alloc_s1(t_line *s1)
{
	if (!s1->content)
	{
		s1->content = malloc(1);
		if (!s1->content)
			return (NULL);
		*s1->content = '\0';
		s1->beg = s1->content;
	}
	return (s1->content);
}

char	*ft_strjoin_free(t_line *s1, char const *s2, const size_t s2_len)
{
	char	*str;
	size_t	i;
	int		total_size;

	alloc_s1(s1);
	if (!s2 || !s1)
		return (NULL);
	total_size = s1->len + s2_len;
	str = alloc_string(total_size);
	if (!str)
		return (NULL);
	i = 0;
	while (total_size--)
	{
		if (i < s1->len)
			str[i] = s1->content[i];
		else
			str[i] = s2[i - s1->len];
		i++;
	}
	str[i] = '\0';
	s1->len = i;
	free((void *)s1->beg);
	free((void *)s2);
	return (str);
}
