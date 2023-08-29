/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:50:06 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/29 06:50:06 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero(void *s, size_t n)
{
	int				i;
	unsigned char	*p;

	p = (unsigned char *)s;
	if (n)
	{
		i = 0;
		while (n--)
		{
			p[i] = 0;
			i++;
		}
	}
}
