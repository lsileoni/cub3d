/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:52:37 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/29 06:52:37 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned char	*p;
	size_t			i;

	if (!s || !f)
		return (NULL);
	p = mmu_op(MMU_ALLOC, (ft_strlen(s) + 1));
	i = 0;
	while (i < ft_strlen(s))
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return ((char *)p);
}
