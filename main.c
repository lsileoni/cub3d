#include "./libft/src/libft.h"

#include "cub3d.h"
#include "graphics.h"

int	main(int argc, char **argv)
{
	int			**grid;
	t_gameinfo	info;
	t_graphics	*graphics;


	mmu_op(MMU_CREATE, 0);
	if (argc < 2)
	{
		ft_printf("Too few arguments!\n");
		return (1);
	}
	info.row_size = get_row_size(argv[1]);
	info.col_size = get_col_size(argv[1]);
	grid = mmu_op(MMU_ALLOC, (sizeof(void *) * info.col_size));
	extract_grid(grid, argv[1], &info);
	flood_fill(grid, info);
	if (!check_validity(grid, info))
	{
		ft_printf("Invalid map!\n");
		return (1);
	}
	restore_grid(grid, info);
	print_grid(grid, info);
	graphics = init_graphics(grid, &info);
	start_loop(graphics);
	mlx_terminate(graphics->mlx); // put in in the exit functions (ESC, etc.)
	return (0);
}
