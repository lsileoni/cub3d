/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:44:12 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/25 19:36:41 by lsileoni         ###   ########.fr       */
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
	MMU_CREAT,
	MMU_ALLOC,
	MMU_FREE,
	MMU_EXIT
};

void	*mmu_op(int op, size_t data);
void	mmu_exit(t_list *pointers);
void	*mmu_alloc(t_mmu *mmu, size_t size);
void	mmu_creat(t_mmu *mmu);
void	mmu_free(t_mmu *mmu, void *adr);

#endif
