/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:52:28 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/29 06:52:29 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	rval;

	rval = ft_strlen(src);
	if (!*src)
		return (rval * (*dst = '\0'));
	if (dstsize)
	{
		i = 0;
		while (i < (dstsize - 1) && *src)
		{
			*dst = *src;
			dst++;
			src++;
			i++;
		}
		*dst = '\0';
	}
	return (rval);
}
