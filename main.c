#include "./libft/src/libft.h"

typedef struct s_mmu
{
	t_list	*pointers;
	size_t	count;
} 			t_mmu;

enum e_mmu_ops
{
	MMU_CREAT,
	MMU_ALLOC,
	MMU_FREE,
	MMU_EXIT
};
void	mmu_exit(t_list *pointers);

void	*mmu_alloc(t_list *pointers, size_t size)
{
	void	*ptr;

	ptr = malloc(sizeof(size));
	ft_printf("size is %d and ptr is %p\n", size, ptr);
	if (!ptr)
		mmu_exit(pointers);
	ft_lstadd_back(&pointers, ptr);
	return (ptr);
}

void	mmu_creat(t_mmu *mmu)
{
	mmu->pointers = ft_lstnew(NULL);
	mmu->count = 0;
}

void	*mmu_free()
{
	return (NULL);
}

void	mmu_exit(t_list *pointers)
{
	ft_lstiter(pointers, free);
	exit (0);
}

void	*mmu_op(int op, size_t data)
{
	static t_mmu	mmu = {NULL};

	if (op == MMU_CREAT)
		mmu_creat(&mmu);
	else if (op == MMU_ALLOC)
		return (mmu_alloc(mmu.pointers, data));
	else if (op == MMU_FREE)
		return (mmu_free());
	else if (op == MMU_EXIT)
		mmu_exit(mmu.pointers);
	return (NULL);
}

#include <stdio.h>

int main(void)
{
	(void)mmu_op(MMU_CREAT, 0);
	char	*str = mmu_op(MMU_ALLOC, 64);

	for (int i = 0; i < 63; i++)
		str[i] = (i % 23) + 'a';
	str[63] = '\0';
	ft_printf("%s", str);
	mmu_op(MMU_EXIT, 0);
	return (0);
}
