/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_lowercase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:40:08 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/28 09:37:30 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_to_lowercase(char *str)
{
	char	*storage;
	int		i;

	if (!str)
		return (NULL);
	storage = mmu_op(MMU_ALLOC, (ft_strlen(str) + 1));
	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
				storage[i] = ft_tolower(str[i]);
			else
				storage[i] = str[i];
		}
		else
			storage[i] = str[i];
		i++;
	}
	storage[i] = '\0';
	return (storage);
}
