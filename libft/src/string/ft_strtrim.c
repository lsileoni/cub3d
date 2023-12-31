/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:52:56 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/29 06:52:56 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	in_set(char c, char const *set)
{
	int	i;

	i = 0;
	if (set)
	{
		while (set[i])
		{
			if (set[i] == c)
				return (1);
			i++;
		}
	}
	return (0);
}

static int	seek_beginning(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (*s1)
	{
		if (!in_set(*s1, set))
			break ;
		s1++;
		i++;
	}
	return (i);
}

static int	seek_ending(const char *s1, char const *set)
{
	int	i;

	if (!*s1)
		return (0);
	i = 0;
	while (s1[i + 1])
		i++;
	while (i)
	{
		if (!in_set(s1[i], set))
			break ;
		i--;
	}
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned char	*ret;
	int				beg;
	int				end;
	int				i;

	if (!s1)
		return (0);
	beg = seek_beginning(s1, set);
	end = seek_ending(s1, set);
	if (beg > end)
	{
		ret = mmu_op(MMU_ALLOC, 1);
		*ret = '\0';
		return ((char *)ret);
	}
	ret = mmu_op(MMU_ALLOC, ((end - beg) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (beg < end)
		ret[i++] = s1[beg++];
	ret[i] = '\0';
	return ((char *)ret);
}
