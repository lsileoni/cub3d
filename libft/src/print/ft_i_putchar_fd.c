/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i_putchar_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:50:53 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/29 06:50:54 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_i_putchar_fd(char c, int fd)
{
	int	w_ret;

	w_ret = write(fd, &c, 1);
	if (w_ret <= 0)
		return (0);
	return (w_ret);
}
