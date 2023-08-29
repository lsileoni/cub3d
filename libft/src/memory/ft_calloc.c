/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:50:11 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/29 06:50:11 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	i;

	if (!count || !size)
		return (ft_calloc(1, 1));
	i = count * size;
	if (i / count != size)
		return (NULL);
	p = mmu_op(MMU_ALLOC, i);
	ft_bzero(p, i);
	return (p);
}
