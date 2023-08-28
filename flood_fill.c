#include "cub3d.h"
#include "libft/src/libft.h"

static void updateStack(int **grid, t_stack_pair *sp, t_i_point p, t_gameinfo info)
{
	int	d;
	int new_x;
	int new_y;
	const int dx[] = {-1, 1, 0, 0};
	const int dy[] = {0, 0, -1, 1};

	d = 0;
	while (d < 4)
	{
		new_x = p.x + dx[d];
		new_y = p.y + dy[d];
		if (new_x >= 0 && new_x < info.col_size && new_y >= 0 && \
				new_y < info.row_size && grid[new_x][new_y] == TARGET_COLOR)
		{
			sp->stack_x[sp->stack_size] = new_x;
			sp->stack_y[sp->stack_size] = new_y;
			sp->stack_size++;
		}
		d++;
	}
}

void floodFill(int **grid, t_gameinfo info)
{
	t_i_point		p;
	t_stack_pair	sp;

    if (info.start_x < 0 || info.start_x >= info.col_size || info.start_y < 0 || \
			info.start_y >= info.row_size || grid[info.start_x][info.start_y] != TARGET_COLOR)
        return;
	sp.stack_x = mmu_op(MMU_ALLOC, (sizeof(int) * (info.row_size * info.col_size)));
	sp.stack_y = mmu_op(MMU_ALLOC, (sizeof(int) * (info.row_size * info.col_size)));
    sp.stack_size = 0;
    sp.stack_x[sp.stack_size] = info.start_x;
    sp.stack_y[sp.stack_size] = info.start_y;
    sp.stack_size++;
    while (sp.stack_size > 0)
	{
        p.x = sp.stack_x[sp.stack_size - 1];
        p.y = sp.stack_y[sp.stack_size - 1];
        sp.stack_size--;

        grid[p.x][p.y] = REPLACEMENT_COLOR;
		updateStack(grid, &sp, p, info);
    }
	mmu_op(MMU_FREE, (size_t)sp.stack_x);
	mmu_op(MMU_FREE, (size_t)sp.stack_y);
}
