/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 07:37:09 by lsileoni          #+#    #+#             */
/*   Updated: 2023/10/08 14:20:01 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long long	get_message_hash(const char *message)
{
	long long	hash;

	if (!message)
		return (0);
	hash = FNV_OFFSET;
	while (*message)
	{
		hash = hash ^ *message;
		hash = hash * FNV_PRIME;
		message++;
	}
	return (hash);
}

int	ft_restructure_table(t_htable *table, const char *key, void *value)
{
	t_htable			*tmp;
	unsigned int		i;

	tmp = ft_htable_create(table->cap * 2);
	if (!tmp)
		return (-1);
	i = 0;
	while (i < table->cap)
	{
		ft_htable_insert(tmp, table->memory[i]->key, table->memory[i]->value);
		mmu_op(MMU_FREE, (size_t)table->memory[i]);
		i++;
	}
	ft_htable_insert(tmp, key, value);
	mmu_op(MMU_FREE, (size_t)table->memory);
	table->memory = tmp->memory;
	mmu_op(MMU_FREE, (size_t)tmp);
	table->cap *= 2;
	table->size++;
	return (1);
}

int	remove_htable_elem(t_htable *table, unsigned long long key_hash)
{
	mmu_op(MMU_FREE,
		(size_t)((void *)table->memory[key_hash % table->cap]->key));
	mmu_op(MMU_FREE, (size_t)table->memory[key_hash % table->cap]->value);
	mmu_op(MMU_FREE, (size_t)table->memory[key_hash % table->cap]);
	table->memory[key_hash % table->cap] = NULL;
	return (0);
}

static int	assign_value(t_htable *table, const char *key,
						char *value, size_t index)
{
	char	*dup_key;

	dup_key = ft_strdup(key);
	if (!(dup_key))
		return (-1);
	table->memory[index] = mmu_op(MMU_ALLOC, sizeof(t_htelem));
	table->memory[index]->key = dup_key;
	table->memory[index]->value = value;
	table->size++;
	return (1);
}

int	ft_probe_table(t_htable *table, const char *key, void *value)
{
	unsigned long long	key_hash;
	unsigned long long	index;

	key_hash = get_message_hash(key);
	while (1)
	{
		index = key_hash % table->cap;
		if (!table->memory[index])
			return (assign_value(table, key, value, index));
		else if (!ft_strncmp(key, table->memory[index]->key, \
					ft_strlen(key)))
		{
			if (table->memory[index]->value)
				mmu_op(MMU_FREE, (size_t)table->memory[index]->value);
			table->memory[index]->value = value;
			break ;
		}
		key_hash++;
	}
	return (1);
}
