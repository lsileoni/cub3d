/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:44:12 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/25 19:57:36 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MMU_H
# define MMU_H
# include "./libft/src/libft.h"

typedef struct s_mmu
{
	t_list	*pointers;
	size_t	count;
}			t_mmu;

enum e_mmu_ops
{
	MMU_CREATE,
	MMU_ALLOC,
	MMU_FREE,
	MMU_DESTROY
};

void	*mmu_op(int op, size_t data);
void	mmu_destroy(t_list *pointers, size_t flag);
void	*mmu_alloc(t_mmu *mmu, size_t size);
void	mmu_create(t_mmu *mmu);
void	mmu_free(t_mmu *mmu, void *adr);

#endif
