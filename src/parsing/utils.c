/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:32:48 by jofoto            #+#    #+#             */
/*   Updated: 2023/09/22 13:33:10 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/src/libft.h"

char	*strdup_nl(char *str)
{
	char	*p;
	int		i;

	if(str == NULL)
		return (NULL);
	p = mmu_op(MMU_ALLOC, ft_strlen(str) + 1);
	i = 0;
	while (*str && *str != '\n')
	{
		*p = *str;
		str++;
		p++;
		i++;
	}
	*p = '\0';
	return ((char *)p - i);
}