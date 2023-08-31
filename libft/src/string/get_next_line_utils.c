/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:53:06 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/29 12:14:41 by lsileoni         ###   ########.fr       */
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

	p = mmu_op(MMU_ALLOC, (len + 1));
	return (p);
}

static void	*alloc_s1(t_line *s1)
{
	if (!s1->content)
	{
		s1->content = mmu_op(MMU_ALLOC, 1);
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
	mmu_op(MMU_FREE, (size_t)((void *)s1->beg));
	mmu_op(MMU_FREE, (size_t)((void *)s2));
	return (str);
}
