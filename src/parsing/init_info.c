/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:31:53 by jofoto            #+#    #+#             */
/*   Updated: 2023/09/30 14:29:19 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/src/libft.h"

/**
 * check if it ends with .cub
**/

static void	validate_file_type(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len >= 4)
	{
		if (ft_strncmp(file + len - 4, ".cub", 5) == 0)
			return ;
	}
	p_free_exit(6, "Error\nWrong file type, must end with .cub\n");
}

void	init_info(char *file, t_gameinfo *info)
{
	int	fd;

	validate_file_type(file);
	ft_bzero(info, sizeof(t_gameinfo));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		p_free_exit(3, "Error\nFile not Found\n");
	if (get_textures(fd, info) != 0)
	{
		close(fd);
		p_free_exit(4, "Error\nInsufficient information or wrong format!\n");
	}
	get_grid(fd, info);
}