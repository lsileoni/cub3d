/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:51:29 by lsileoni          #+#    #+#             */
/*   Updated: 2023/09/30 21:26:59 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_number(int n)
{
	char	*str;
	int		rval;

	str = ft_itoa(n);
	if (!str)
		return (0);
	ft_putstr_fd(str, 1);
	rval = ft_strlen(str);
	mmu_op(MMU_FREE, (size_t)str);
	return (rval);
}

int	print_unumber(unsigned int n)
{
	char	*str;
	int		rval;

	str = ft_uitoa_base(n, 10);
	if (!str)
		return (0);
	ft_putstr_fd(str, 1);
	rval = ft_strlen(str);
	if (ft_strlen(str) == 0)
		rval++;
	mmu_op(MMU_FREE, (size_t)str);
	return (rval);
}

int	print_string(char *s)
{
	int	rval;

	rval = 0;
	if (s)
	{
		while (*s)
		{
			rval += ft_i_putchar_fd(*s, 1);
			s++;
		}
	}
	else
	{
		ft_putstr_fd("(null)", 1);
		rval += 6;
	}
	return (rval);
}

int	print_pointer(unsigned long long pval)
{
	char	*temp;
	int		rval;

	ft_putstr_fd("0x", 1);
	temp = ft_ulltoa_base(pval, 16);
	if (!temp)
		return (0);
	rval = 0;
	if (!*temp)
	{
		ft_putchar_fd('0', 1);
		rval++;
	}
	else
		ft_putstr_fd(temp, 1);
	rval += ft_strlen(temp) + 2;
	mmu_op(MMU_FREE, (size_t)temp);
	temp = NULL;
	return (rval);
}

int	print_hex(unsigned int n, unsigned char uppercase)
{
	int		rval;
	char	*case_hex;
	char	*hex;

	rval = 0;
	hex = ft_uitoa_base(n, 16);
	if (!hex)
		return (0);
	if (uppercase)
		case_hex = ft_to_uppercase(hex);
	else
		case_hex = ft_to_lowercase(hex);
	ft_putstr_fd(case_hex, 1);
	rval += ft_strlen(case_hex);
	mmu_op(MMU_FREE, (size_t)hex);
	mmu_op(MMU_FREE, (size_t)case_hex);
	return (rval);
}
