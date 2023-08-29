/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:36:29 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/28 09:08:53 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*mmu_op(int op, size_t data)
{
	static t_mmu	mmu = {NULL, 0};

	if (op == MMU_CREATE)
		mmu_create(&mmu);
	else if (op == MMU_ALLOC)
		return (mmu_alloc(&mmu, data));
	else if (op == MMU_FREE)
		mmu_free(&mmu, (void *)data);
	else if (op == MMU_DESTROY)
		mmu_destroy(mmu.pointers, data);
	return (NULL);
}
