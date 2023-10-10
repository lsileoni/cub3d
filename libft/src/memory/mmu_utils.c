/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmu_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:25:34 by lsileoni          #+#    #+#             */
/*   Updated: 2023/10/08 14:20:23 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	mmu_destroy(t_list *pointers, size_t flag)
{
	t_list	*tmp;

	while (pointers)
	{
		tmp = pointers->next;
		free(pointers->content);
		free(pointers);
		pointers = tmp;
	}
	if (flag)
		exit (0);
}

void	*mmu_alloc(t_mmu *mmu, size_t size)
{
	t_list	*nelem;
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		mmu_destroy(mmu->pointers, 1);
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

void	mmu_create(t_mmu *mmu)
{
	mmu->pointers = ft_lstnew(NULL);
	mmu->count = 0;
}

static void	mmu_free_probe(t_mmu *mmu, void *adr, t_list *cur)
{
	t_list	*prev;

	prev = cur;
	while (cur)
	{
		if (cur->content == adr)
		{
			prev->next = cur->next;
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
		free(mmu->pointers->content);
		mmu->pointers->content = NULL;
		mmu->count -= 1;
		return ;
	}
	cur = mmu->pointers;
	if (cur->content == adr)
	{
		mmu->pointers = cur->next;
		free(cur->content);
		free(cur);
		mmu->count -= 1;
		return ;
	}
	mmu_free_probe(mmu, adr, cur);
}
