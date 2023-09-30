/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/30 21:52:04 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/src/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 640
#define PLAYER_SIZE 30
#define MOUSE_SENSITIVITY 0.001
#define BLOCK_SIZE 64.0 // maybe this should be an int so we can change it depending on map size

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

//draw.c
void		draw_player(t_player *player);
void		connect_points(mlx_image_t *img, t_point point0, t_point point1, uint32_t color);
void		draw_map(t_map	*map);
void		init_graphics(t_graphics *graphics, t_gameinfo *info);

//main_loop.c
void		start_loop(t_graphics	*graphics);
void		ray(t_graphics *graphics);
uint32_t	rgbaToInteger(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
