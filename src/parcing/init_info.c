#include "../../includes/cub3d.h"
#include "../../libft/src/libft.h"

void	init_info(char *file, t_gameinfo *info)
{
	int	fd;

	ft_bzero(info, sizeof(t_gameinfo));
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nFile '%s' not found!\n");
		return ; // instead of return exit
	}
	if (get_textures(fd, info) != 0)
	{
		ft_printf("Error\nInsufficient information!\n");
		return ;
	}
}
