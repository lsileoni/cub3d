/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/08 13:36:14 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/src/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000
#define PLAYER_SIZE 30
#define MOUSE_SENSITIVITY 0.001
#define FOURTY_FIVE_DEG 0.785398163f
#define BLOCK_SIZE 64.0

enum e_texture_selector
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

typedef struct s_map
{
	int			block_size;
	int			**grid;
	mlx_image_t	*img;
	t_gameinfo	*info;
}				t_map;

typedef struct s_point
{
	double			x;
	double			y;
}					t_point;

typedef	struct	s_player
{
	mlx_image_t		*img;
	t_point			position;
	double			angle;
}					t_player;

typedef struct s_graphics
{
	mlx_t				*mlx;
	t_map				*map;
	t_player			*player;
	mlx_win_cursor_t	*cursor;
	int					ceiling_color;
	int					floor_color;
	mlx_texture_t		*texture_n;
	mlx_texture_t		*texture_w;
	mlx_texture_t		*texture_e;
	mlx_texture_t		*texture_s;
}					t_graphics;

typedef struct s_con_pnt_vars
{
	double			move_ratio;
	double			curr_step;
	int				up;
	int				left;
	int				total_steps;
}					t_conn_pnts_vars;

typedef struct s_dda_vars
{
	double	dx;
	double	dy;
	double	x_step;
	double	y_step;
	double	x;
	double	y;
	double	sidelen_x;
	double	sidelen_y;
	double	ray_x;
	double	ray_y;
	double	end_distance;
	int		last_move;
	int		map_y;
	int		map_x;
	t_point	curr_pos;
	t_point	end;
	t_point	start;
}			t_dda_vars;

typedef struct s_ray_vars
{
	double			dist;
	double			depth;
	int				t_sel;
	unsigned char	north;
	unsigned char	west;
}					t_ray_vars;

typedef struct s_loop_vars
{
	double	current_angle;
	double	step_size;
	int		pixels_to_draw;
	int		texture_index_x;
	int		texture_index_y;
	int		j;
	int		i;
	int		test;
}			t_loop_vars;

// draw.c
void			draw_player(t_player *player);
void			connect_points(mlx_image_t *img, t_point point0, t_point point1, uint32_t color);
void			draw_map(t_map	*map);
void			init_graphics(t_graphics *graphics, t_gameinfo *info);

// main_loop.c
void			start_loop(t_graphics	*graphics);

// ray.c
void			ray(t_graphics *graphics);

// utils.c
int				mlx_pixel_get(mlx_texture_t *texture,
				int texture_index_x, int texture_index_y);
unsigned int	rgba_to_int(unsigned char r, unsigned char g,
				unsigned char b, unsigned char a);
void			reset_current_angle(double *current_angle);
void			paint_ceiling_floor(t_graphics *graphics);

// dda.c
void			perform_dda(t_ray_vars *rvars, t_dda_vars *dvars, int **grid);

// endpoint.c
void			set_endpoint(t_graphics *graphics, t_point *end,
				t_point start, double angle);

// setters.c
void			set_north_west(t_ray_vars *vars, double angle);
void			set_direction_depth(t_dda_vars *dvars,
				t_ray_vars *vars, double angle);
void			set_ray_vars(t_graphics *graphics, double angle, t_ray_vars *vars);
void			set_texture_x(t_graphics *graphics,
				t_ray_vars *vars, int *texture_index_x);
