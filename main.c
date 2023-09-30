#include "cub3d.h"
#include "graphics.h"

int	main(int argc, char **argv)
{
	int			**grid;
	t_gameinfo	info;
	t_graphics	graphics;


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
	printf("%d, %d\n", info.row_size, info.col_size);
	if (!check_validity(grid, info))
	{
		ft_printf("Invalid map!\n");
		return (1);
	}
	restore_grid(grid, info);
	print_grid(grid, info);
	init_graphics(&graphics, grid, &info);
	mlx_texture_t* texture = mlx_load_png("./RedwallL.png");
	graphics.texture_n = texture;
	texture = mlx_load_png("./MultibrickD.png");
	graphics.texture_w = texture;
	texture = mlx_load_png("./Stone.png");
	graphics.texture_e = texture;
	texture = mlx_load_png("./WoodbrickL.png");
	graphics.texture_s = texture;
	start_loop(&graphics);
	mlx_terminate(graphics.mlx); // put in in the exit functions (ESC, etc.)
	return (0);
}
