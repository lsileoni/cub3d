/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:52:24 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/29 06:52:24 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	char	*dst_beg;
	int		i;

	dst_beg = dst;
	src_len = ft_strlen(src);
	i = dstsize;
	if ((!dst_beg || !src) && !dstsize)
		return (dstsize + src_len);
	while (*dst_beg && i--)
		dst_beg++;
	dst_len = dst_beg - dst;
	i = dstsize - dst_len;
	if (!i)
		return (dst_len + src_len);
	while (*src && i-- != 1)
		*dst_beg++ = *src++;
	*dst_beg = '\0';
	return (dst_len + src_len);
}
