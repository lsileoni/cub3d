/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:56:56 by lsileoni          #+#    #+#             */
/*   Updated: 2023/09/30 21:57:06 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../MLX42/include/MLX42/MLX42.h"
#include "../../includes/graphics.h"
#include <math.h>

typedef struct s_ray_vars
{
	double			dist;
	float			move_ratio;
	float			curr_step;
	int				up;
	int				left;
	int				last_move;
	t_point			curr_pos;
	t_point			blockpos;
	double			depth;
	int				t_sel;
}					t_ray_vars;

static t_ray_vars	get_ray_vars(t_graphics *graphics, t_player *player, int **map, double angle)
{
	t_ray_vars	vars;
	int			north;
	int			west;
	double		x1;
	double		x2;
	double		y1;
	double		y2;
	double		dx;
	double		dy;
	double		ddist_x;
	double		ddist_y;
	double		sidelen_x;
	double		sidelen_y;
	double		x;
	double		y;
	double		step;
	double		x_step;
	double		y_step;
	double		end_distance;
	double		angle_diff;
	int			map_x;
	int			map_y;
	int			x_steps = 0;
	int			y_steps = 0;
	int			itercount = 0;
	double		fourty_five_deg = 0.785398163;
	double		x_max = graphics->map->info->row_size;
	double		x_min = 1.0;
	double		y_max = graphics->map->info->col_size;
	double		y_min = 1.0;

	x1 = player->position.x / BLOCK_SIZE;
	y1 = player->position.y / BLOCK_SIZE;
	if ((angle >= M_PI / 2.0) && angle <= ((3 * M_PI)/2.0))
		west = 0;
	else
		west = 1;
	if ((angle <= M_PI) && angle >= 0)
		north = 1;
	else
		north = 0;
	if (angle < (((M_PI * 3) / 2.0) + 0.00001) && angle > (((M_PI * 3) / 2.0) - 0.00001))
	{
		y2 = 1.0;
		x2 = x1 + 0.125;
	}
	else if (angle > 0.0 && angle <= M_PI / 2.0)
	{
		angle_diff = angle;
		if (angle_diff > fourty_five_deg)
		{
			y2 = y_max;
			angle_diff -= M_PI / 4.0;
			angle_diff = (M_PI / 4.0) - angle_diff;
			x2 = ((y2 - y1) * tan(angle_diff)) + x1;
		}
		else
		{
			x2 = x_max;
			y2 = ((x2 - x1) * tan(angle_diff)) + y1;
		}
	}
	else if (angle > M_PI / 2.0 && angle <= M_PI)
	{
		angle_diff = fabs(fabs(angle - M_PI) - (M_PI / 2.0));
		if (angle_diff > fourty_five_deg)
		{
			x2 = 1.0;
			angle_diff -= M_PI / 4.0;
			angle_diff = (M_PI / 4.0) - angle_diff;
			y2 = ((x1 - x2) * tan(angle_diff)) + y1;
		}
		else
		{
			y2 = y_max;
			x2 = ((y1 - y2) * tan(angle_diff)) + x1;
		}
	}
	else if (angle > M_PI && angle <= (3.0 * M_PI) / 2.0)
	{
		angle_diff = fabs(angle - M_PI);
		if (angle_diff > fourty_five_deg)
		{
			y2 = 1.0;
			angle_diff -= M_PI / 4.0;
			angle_diff = (M_PI / 4.0) - angle_diff;
			x2 = ((y2 - y1) * tan(angle_diff)) + x1;
		}
		else
		{
			x2 = 1.0;
			y2 = ((x2 - x1) * tan(angle_diff)) + y1;
		}
	}
	else
	{
		angle_diff = fabs(fabs(angle - (M_PI * 2.0)) - (M_PI / 2.0));
		if (angle_diff > fourty_five_deg)
		{
			x2 = x_max;
			angle_diff -= M_PI / 4.0;
			angle_diff = (M_PI / 4.0) - angle_diff;
			y2 = ((x1 - x2) * tan(angle_diff)) + y1;
		}
		else
		{
			y2 = 1.0;
			x2 = ((y1 - y2) * tan(angle_diff)) + x1;
		}
	}
	dx = (x2 - x1);
	dy = (y2 - y1);
	if (dx == 0)
		x_step = 1e30;
	else
		x_step = sqrt(1 + ((dy / dx) * (dy / dx)));
	if (dy == 0)
		y_step = 1e30;
	else
		y_step = sqrt(1 + ((dx / dy) * (dx / dy)));
	map_x = (int)x1;
	map_y = (int)y1;
	if (dx < 0)
	{
		x = -1;
		sidelen_x = (x1 - (double)map_x) * x_step;
	}
	else
	{
		x = 1;
		sidelen_x = (((double)(map_x + 1.0)) - x1) * x_step;
	}
	if (dy < 0)
	{
		y = -1;
		sidelen_y = (y1 - (double)map_y) * y_step;
	}
	else
	{
		y = 1;
		sidelen_y = (((double)(map_y + 1.0)) - y1) * y_step;
	}
	vars.curr_pos.x = x1;
	vars.curr_pos.y = y1;
	double ray_x = x1;
	double ray_y = y1;
	while (1)
	{
		if (sidelen_x < sidelen_y)
		{
			end_distance = sidelen_x;
			sidelen_x += x_step;
			map_x += x;
			ray_x += x;
			vars.last_move = 1;
		}
		else
		{
			end_distance = sidelen_y;
			sidelen_y += y_step;
			map_y += y;
			ray_y += y;
			vars.last_move = 2;
		}
		if (map[map_y][map_x] == 1)
		{
			vars.curr_pos.x = map_x * BLOCK_SIZE;
			vars.curr_pos.y = map_y * BLOCK_SIZE;
			break ;
		}
		itercount++;
	}
	vars.dist = end_distance;

	double current_angle = player->angle - angle;

	if (vars.last_move == 2)
	{
		if (north)
			vars.t_sel = NORTH;
		else
			vars.t_sel = SOUTH;
		vars.depth = cos(angle) * end_distance + x1;
	}
	else
	{
		if (west)
			vars.t_sel = WEST;
		else
			vars.t_sel = EAST;
		vars.depth = sin(angle) * end_distance + y1;
	}
	vars.depth -= floor(vars.depth);
	if (current_angle < 0)
	  current_angle += 2 * M_PI;
	if (current_angle > 2 * M_PI)
	  current_angle -= 2 * M_PI;
	vars.dist = vars.dist * cos(current_angle);
	return (vars);
}
uint32_t rgbaToInteger(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return (r << 24) | (g << 16) | (b << 8) | a;
}

int	mlx_pixel_get(mlx_texture_t *texture, int texture_index_x, int texture_index_y)
{
	unsigned char rgba[4];
	int	t;

	if (texture_index_x >= 0 && texture_index_x < texture->width && texture_index_y >= 0 && texture_index_y < texture->height)
    {
        size_t pixelIndex = (texture_index_y * texture->width + texture_index_x) * texture->bytes_per_pixel;

        rgba[0] = texture->pixels[pixelIndex];
        rgba[1] = texture->pixels[pixelIndex + 1];
        rgba[2] = texture->pixels[pixelIndex + 2];
        rgba[3] = texture->pixels[pixelIndex + 3];
    }
	else
		return (0);
    return (rgbaToInteger(rgba[0], rgba[1], rgba[2], rgba[3]));
}

void	ray(t_graphics *graphics)
{
	t_ray_vars		vars;
	double			left_angle;
	double			current_angle;
	double			step_size;
	double			max_wall_size;
	int				pixels_to_draw;
	double			depth_step;
	unsigned char 	color[4];

	depth_step = (WINDOW_HEIGHT / 6.0) / 255.0;
	for (int i = 0; i < WINDOW_WIDTH; i++)
	{
		for (int j = 0; j < WINDOW_HEIGHT; j++)
		{
			if (j > WINDOW_HEIGHT / 2)
				mlx_put_pixel(graphics->map->img, i, j, graphics->ceiling_color);
			else
				mlx_put_pixel(graphics->map->img, i, j, graphics->floor_color);
		}
	}
	step_size = (0.001171875 * 1.1);
	left_angle = graphics->player->angle - ((step_size * WINDOW_WIDTH) / 2);
	current_angle = left_angle;
	for (int i = 0; i < WINDOW_WIDTH; i++)
	{
		int over = 0;
		if (current_angle < 0)
		  current_angle += 2 * M_PI;
		if (current_angle > 2 * M_PI)
		  current_angle -= 2 * M_PI;
		vars = get_ray_vars(graphics, graphics->player, graphics->map->grid, current_angle);
		pixels_to_draw = (70.0 * WINDOW_HEIGHT) / (vars.dist * 64.0);
		color[1] = (unsigned char)(0xFF * vars.depth);
		color[2] = 0x00;
		if (pixels_to_draw > 255)
			color[3] = 255;
		else
			color[3] = pixels_to_draw;
		int texture_index_x;
		if (vars.t_sel == WEST)
			texture_index_x = vars.depth * graphics->texture_w->width;
		else if (vars.t_sel == NORTH)
			texture_index_x = vars.depth * graphics->texture_n->width;
		else if (vars.t_sel == SOUTH)
			texture_index_x = vars.depth * graphics->texture_s->width;
		else
			texture_index_x = vars.depth * graphics->texture_e->width;
		int test = 0;
		for (int j = (WINDOW_HEIGHT / 2) - (pixels_to_draw / 2); j < ((WINDOW_HEIGHT / 2) - (pixels_to_draw / 2)) + pixels_to_draw; j++)
		{
			if(j < 0)
			{
				test = j * -1;
				j = 0;
			}
			if(j > WINDOW_HEIGHT - 1)
				break ;

			if (vars.t_sel == WEST)
			{
				int texture_index_y = test * ((double)graphics->texture_w->height/ (double)(pixels_to_draw + (over / 8.0)));
				mlx_put_pixel(graphics->map->img, i, j, mlx_pixel_get(graphics->texture_w, texture_index_x, texture_index_y));
			}
			else if (vars.t_sel == NORTH)
			{
				int texture_index_y = test * ((double)graphics->texture_n->height/ (double)(pixels_to_draw + (over / 8.0)));
				mlx_put_pixel(graphics->map->img, i, j, mlx_pixel_get(graphics->texture_n, texture_index_x, texture_index_y));
			}
			else if (vars.t_sel == SOUTH)
			{
				int texture_index_y = test * ((double)graphics->texture_s->height/ (double)(pixels_to_draw + (over / 8.0)));
				mlx_put_pixel(graphics->map->img, i, j, mlx_pixel_get(graphics->texture_s, texture_index_x, texture_index_y));
			}
			else
			{
				int texture_index_y = test * ((double)graphics->texture_e->height/ (double)(pixels_to_draw + (over / 8.0)));
				mlx_put_pixel(graphics->map->img, i, j, mlx_pixel_get(graphics->texture_e, texture_index_x, texture_index_y));
			}
			test++;
		}
		current_angle += step_size;
	}
}