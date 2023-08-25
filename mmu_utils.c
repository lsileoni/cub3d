/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmu_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:25:34 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/25 19:28:05 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmu.h"

void	mmu_exit(t_list *pointers)
{
	t_list	*tmp;

	while (pointers)
	{
		tmp = pointers->next;
		ft_printf("freeing on exit %p\n", pointers->content);
		free(pointers->content);
		free(pointers);
		pointers = tmp;
	}
	exit (0);
}

void	*mmu_alloc(t_mmu *mmu, size_t size)
{
	t_list	*nelem;
	void	*ptr;

	ptr = malloc(size);
	ft_printf("Allocated: %p\n", ptr);
	if (!ptr)
		mmu_exit(mmu->pointers);
	if (mmu->count == 0)
		mmu->pointers->content = ptr;
	else
	{
		nelem = ft_lstnew(ptr);
		ft_lstadd_back(&(mmu->pointers), nelem);
	}
	mmu->count += 1;
	return (ptr);
}

void	mmu_creat(t_mmu *mmu)
{
	mmu->pointers = ft_lstnew(NULL);
	mmu->count = 0;
}

static void	mmu_free_probe(t_mmu *mmu, void *adr, t_list *cur)
{
	t_list	*prev;

	while (cur)
	{
		if (cur->content == adr)
		{
			prev->next = cur->next;
			ft_printf("freeing 3 %p\n", cur->content);
			free(cur->content);
			free(cur);
			mmu->count -= 1;
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	mmu_free(t_mmu *mmu, void *adr)
{
	t_list	*cur;

	if (!mmu->count)
		return ;
	if (mmu->count == 1)
	{
		ft_printf("freeing 1 %p\n", mmu->pointers->content);
		free(mmu->pointers->content);
		mmu->pointers->content = NULL;
		mmu->count -= 1;
		return ;
	}
	cur = mmu->pointers;
	if (cur->content == adr)
	{
		mmu->pointers = cur->next;
		ft_printf("freeing 2 %p\n", cur->content);
		free(cur->content);
		free(cur);
		mmu->count -= 1;
		return ;
	}
	mmu_free_probe(mmu, adr, cur);
}
