/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:52:10 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/29 06:52:11 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s1)
{
	unsigned char	*p;
	unsigned char	*tmp;
	int				i;

	p = mmu_op(MMU_ALLOC, ft_strlen(s1) + 1);
	tmp = (unsigned char *)s1;
	i = 0;
	while (*tmp)
	{
		*p = *tmp;
		tmp++;
		p++;
		i++;
	}
	*p = '\0';
	return ((char *)p - i);
}
