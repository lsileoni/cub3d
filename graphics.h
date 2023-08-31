/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:46:07 by jofoto            #+#    #+#             */
/*   Updated: 2023/08/29 14:05:59 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/src/libft.h"
#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 640
#define PLAYER_SIZE 30
#define MOUSE_SENSITIVITY 0.001
#define BLOCK_SIZE 63 // maybe this should be an int so we can change it depending on map size

typedef struct s_point
{
	int				x;
	int				y;
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
	mlx_image_t			*map;
	t_player			*player;
	mlx_win_cursor_t	*cursor;
}					t_graphics;

typedef struct s_con_pnt_vars
{
	float			move_ratio;
	float			curr_step;
	int				up;
	int				left;
	int				total_steps;
}					t_conn_pnts_vars;

//draw.c
void		draw_player(t_player *player);
void		connect_points(mlx_image_t *img, t_point point0, t_point point1, uint32_t color);
void		draw_map(mlx_image_t *map);

//init.c
void	init_graphics(t_graphics *graphics);

//main_loop.c
void		start_loop(t_graphics	*graphics);
