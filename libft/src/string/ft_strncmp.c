/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:52:41 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/29 06:52:41 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 == *s2 && n && *s1 && *s1)
	{
		s1++;
		s2++;
		n--;
	}
	if (*s1 != *s2 && n)
	{
		if (*(unsigned char *)s1 > *(unsigned char *)s2)
			return (1);
		return (-1);
	}
	return (0);
}
