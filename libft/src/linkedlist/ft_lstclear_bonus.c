/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:49:12 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/29 06:49:13 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;
	t_list	*curr;

	if (!lst || !del)
		return ;
	curr = *lst;
	while (curr->next)
	{
		next = curr->next;
		ft_lstdelone(curr, del);
		curr = next;
	}
	ft_lstdelone(curr, del);
	*lst = NULL;
}
