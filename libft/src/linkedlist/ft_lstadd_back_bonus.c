/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:49:04 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/29 06:49:04 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *_new)
{
	t_list	*last_node;

	if (lst)
	{
		if (*lst)
		{
			last_node = ft_lstlast(*lst);
			if (last_node)
				last_node->next = _new;
		}
		else
		{
			*lst = _new;
		}
	}
}
