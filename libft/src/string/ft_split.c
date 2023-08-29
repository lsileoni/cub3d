/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 06:53:46 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/28 09:41:21 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	strs_counter(char const *s, char c)
{
	int	i;
	int	flag;
	int	s_index;

	i = 0;
	flag = 1;
	s_index = 0;
	while (s[s_index])
	{
		if (s[s_index] != c && flag)
		{
			flag = 0;
			i++;
		}
		else if (s[s_index] == c && !flag)
			flag = 1;
		s_index++;
	}
	return (i);
}

static void	seek_non_delim(char const *s, char c, int *cont)
{
	while (s[*cont] == c)
		*cont += 1;
}

static char	*construct_string(char const *s, char c, int *cont)
{
	unsigned char	*str;
	int				i;
	int				str_i;

	i = *cont;
	while (s[i] != c && s[i])
		i++;
	str = mmu_op(MMU_ALLOC, (i + 1 - *cont));
	str_i = 0;
	while (s[*cont] != c && s[*cont])
	{
		str[str_i] = s[*cont];
		str_i++;
		*cont += 1;
	}
	str[str_i] = '\0';
	return ((char *)str);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		str_i;
	int		strs_i;
	int		str_count;

	if (!s)
		return (NULL);
	str_count = strs_counter(s, c);
	strs_i = 0;
	str_i = 0;
	strs = mmu_op(MMU_ALLOC, (sizeof(char *) * (str_count + 1)));
	if (str_count < 1)
	{
		strs[strs_i] = NULL;
		return (strs);
	}
	while (str_count-- && s[str_i])
	{
		seek_non_delim(s, c, &str_i);
		strs[strs_i++] = construct_string(s, c, &str_i);
	}
	strs[strs_i] = NULL;
	return (strs);
}
