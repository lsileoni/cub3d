/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:16:51 by lsileoni          #+#    #+#             */
/*   Updated: 2023/10/16 08:57:52 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include "libft.h"
# include "MLX42.h"
# include "cub3d.h"
# include <stdlib.h>
# include <stdio.h>
# define WINDOW_HEIGHT 720
# define WINDOW_WIDTH 720
# define PLAYER_SIZE 30
# define MOUSE_SENSITIVITY 0.001
# define ROTATION_MULTIPLIER 0.025
# define FOURTY_FIVE_DEG 0.785398163f
# define BLOCK_SIZE 64.0

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

typedef struct s_player
{
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

typedef struct s_dda
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
}			t_dda;

typedef struct s_ray
{
	double			dist;
	double			depth;
	int				t_sel;
	unsigned char	north;
	unsigned char	west;
}					t_ray;

typedef struct s_loop
{
	double	current_angle;
	double	step_size;
	int		pixels_to_draw;
	int		texture_index_x;
	int		texture_index_y;
	int		j;
	int		i;
	int		texture_bound;
}			t_loop;

void			init_graphics(t_graphics *graphics, t_gameinfo *info);
void			key_press(void *ptr);
void			cursor_func(double xpos, double ypos, void *dt);
void			render_frame(void *dt);
void			raycasting(t_graphics *graphics);
int				mlx_pixel_get(mlx_texture_t *texture, \
		unsigned int texture_index_x, \
		unsigned int texture_index_y, t_ray *r_vars);
unsigned int	rgba_to_int(unsigned char r, unsigned char g,
					unsigned char b, unsigned char a);
void			reset_current_angle(double *current_angle);
void			paint_ceiling_floor(t_graphics *graphics);
void			perform_dda(t_graphics *graphics, t_ray *rvars, \
		t_dda *d_vars);
void			set_endpoint(t_graphics *graphics, t_point *end,
					t_point start, double angle);
void			set_north_west(t_ray *vars, double angle);
void			set_direction_depth(t_dda *d_vars,
					t_ray *vars, double angle);
void			set_ray(t_graphics *graphics,
					double angle, t_ray *vars);
void			set_texture_x(t_graphics *graphics,
					t_ray *vars, int *texture_index_x);
#endif
