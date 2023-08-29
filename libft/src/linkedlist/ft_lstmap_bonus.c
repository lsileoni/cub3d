/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:49:31 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/29 06:49:32 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tail;
	t_list	*head;

	if (!lst || !f || !del)
		return (NULL);
	head = ft_lstnew(f(lst->content));
	if (!head)
	{
		ft_lstdelone(head, del);
		return (NULL);
	}
	while (lst->next)
	{
		lst = lst->next;
		tail = ft_lstnew(f(lst->content));
		if (!tail)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, tail);
	}
	return (head);
}
