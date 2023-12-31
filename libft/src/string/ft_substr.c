/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:52:59 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/29 06:53:00 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*alloc_string(char const *s, unsigned int start, size_t *len)
{
	char	*p;

	if (start >= ft_strlen(s))
	{
		p = mmu_op(MMU_ALLOC, 1);
		*len = 0;
	}
	else
	{
		if (ft_strlen(s) >= *len)
			p = mmu_op(MMU_ALLOC, (*len + 1));
		else
			p = mmu_op(MMU_ALLOC, (ft_strlen(s) + 1));
	}
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	if (s)
	{
		str = alloc_string(s, start, &len);
		if (!str)
			return (NULL);
		i = 0;
		while (len-- && s[i + start])
		{
			str[i] = s[i + start];
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
