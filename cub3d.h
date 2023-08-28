/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 08:54:59 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/28 09:04:33 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
#include "./libft/src/libft.h"
#include <fcntl.h>
#define TARGET_COLOR 0
#define REPLACEMENT_COLOR 9

typedef struct s_stack_pair
{
	int *stack_x;
	int *stack_y;
	int stack_size;
}		t_stack_pair;

typedef struct s_i_point
{
	int x;
	int y;
}		t_i_point;

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_rgb;

typedef struct s_gameinfo
{
	char	**textures;
	t_rgb	ceiling_color;
	t_rgb	floor_color;
	int		start_x;
	int		start_y;
	int		start_direction;
	int		row_size;
	int		col_size;
}	t_gameinfo;

int		get_row_size(char	*map_name);
int		get_col_size(char *map_name);
void	extract_grid(int **grid, char *map_name, t_gameinfo *info);
void	restore_grid(int **grid, t_gameinfo info);
void	print_grid(int **grid, t_gameinfo info);
int		check_validity(int **grid, t_gameinfo info);
void 	floodFill(int **grid, t_gameinfo info);

#endif