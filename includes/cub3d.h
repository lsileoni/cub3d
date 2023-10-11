/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 08:54:59 by lsileoni          #+#    #+#             */
/*   Updated: 2023/10/11 14:14:49 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/src/libft.h"
# include <fcntl.h>
# include <math.h>
# define TARGET_COLOR 0
# define REPLACEMENT_COLOR 9
# define INT_ARR_NULL 0xDEADBEEF
# define ERR_INIT 1
# define ERR_PARSE 2
# define ERR_CHECK 2

typedef struct s_grid_vec
{
	int	**grid;
	int	row_cap;
	int	curr_rows;
	int	cols;
}		t_grid_vec;

typedef struct s_stack_pair
{
	int	*stack_x;
	int	*stack_y;
	int	stack_size;
}		t_stack_pair;

typedef struct s_i_point
{
	int	x;
	int	y;
}		t_i_point;

typedef struct s_rgb
{
	int				filled;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_rgb;

typedef struct s_gameinfo
{
	char		*north_texture;
	char		*south_texture;
	char		*east_texture;
	char		*west_texture;
	t_rgb		ceiling_color;
	t_rgb		floor_color;
	int			**grid;
	int			player_found;
	int			start_x;
	int			start_y;
	double		start_direction;
	int			row_size;
	int			col_size;
}				t_gameinfo;

int			get_row_size(char	*map_name);
int			get_col_size(char *map_name);
void		extract_grid(int **grid, char *map_name, t_gameinfo *info);
void		restore_grid(int **grid, t_gameinfo info);
void		print_grid(int **grid, t_gameinfo info);
int			check_validity(int **grid, t_gameinfo info);
void		flood_fill(int **grid, t_gameinfo info);
void		init_info(char *file, t_gameinfo *info);
int			get_textures(int fd, t_gameinfo *info);
void		get_grid(int fd, t_gameinfo *info);
void		p_free_exit(int err_no, char *str_to_print);
char		*strdup_nl(char *str);
char		*skip_newlines(int fd);
t_grid_vec	realloc_grid_vec(t_grid_vec	grid_vec);
void		init_grid_vec(t_grid_vec *grid_vec);
char		*seek_after_colon(char *line);
int			validate_digit(char *line);
#endif
