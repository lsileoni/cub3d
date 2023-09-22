/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:31:53 by jofoto            #+#    #+#             */
/*   Updated: 2023/09/22 15:59:13 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/src/libft.h"

void	init_info(char *file, t_gameinfo *info)
{
	int	fd;

	ft_bzero(info, sizeof(t_gameinfo));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		p_free_exit(3, "Error\nFile not Found\n");
	if (get_textures(fd, info) != 0)
		p_free_exit(4, "Error\nInsufficient information!\n");
	//get_grid(fd, info);
}
