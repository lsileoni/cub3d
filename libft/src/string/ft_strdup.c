/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 06:53:52 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/28 09:41:43 by lsileoni         ###   ########.fr       */
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
