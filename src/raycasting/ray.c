/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:56:56 by lsileoni          #+#    #+#             */
/*   Updated: 2023/10/01 16:39:57 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../MLX42/include/MLX42/MLX42.h"
#include "../../includes/graphics.h"
#include <math.h>

typedef struct s_ray_vars
{
	double			dist;
	double			depth;
	int				t_sel;
	unsigned char	north;
	unsigned char	west;
}					t_ray_vars;

static void set_endpoint(t_graphics *graphics, t_point *end, t_point start, double angle)
{
	double angle_diff;

	if (angle < (((M_PI * 3) / 2.0) + 0.00001) && angle > (((M_PI * 3) / 2.0) - 0.00001))
	{
		end->y = 1.0;
		end->x = start.x + 0.125;
	}
	else if (angle > 0.0 && angle <= M_PI / 2.0)
	{
		angle_diff = angle;
		if (angle_diff > FOURTY_FIVE_DEG)
		{
			end->y = graphics->map->info->col_size;
			angle_diff -= M_PI / 4.0;
			angle_diff = (M_PI / 4.0) - angle_diff;
			end->x = ((end->y - start.y) * tan(angle_diff)) + start.x;
		}
		else
		{
			end->x = graphics->map->info->row_size;
			end->y = ((end->x - start.x) * tan(angle_diff)) + start.y;
		}
	}
	else if (angle > M_PI / 2.0 && angle <= M_PI)
	{
		angle_diff = fabs(fabs(angle - M_PI) - (M_PI / 2.0));
		if (angle_diff > FOURTY_FIVE_DEG)
		{
			end->x = 1.0;
			angle_diff -= M_PI / 4.0;
			angle_diff = (M_PI / 4.0) - angle_diff;
			end->y = ((start.x - end->x) * tan(angle_diff)) + start.y;
		}
		else
		{
			end->y = graphics->map->info->col_size;
			end->x = ((start.y - end->y) * tan(angle_diff)) + start.x;
		}
	}
	else if (angle > M_PI && angle <= (3.0 * M_PI) / 2.0)
	{
		angle_diff = fabs(angle - M_PI);
		if (angle_diff > FOURTY_FIVE_DEG)
		{
			end->y = 1.0;
			angle_diff -= M_PI / 4.0;
			angle_diff = (M_PI / 4.0) - angle_diff;
			end->x = ((end->y - start.y) * tan(angle_diff)) + start.x;
		}
		else
		{
			end->x = 1.0;
			end->y = ((end->x - start.x) * tan(angle_diff)) + start.y;
		}
	}
	else
	{
		angle_diff = fabs(fabs(angle - (M_PI * 2.0)) - (M_PI / 2.0));
		if (angle_diff > FOURTY_FIVE_DEG)
		{
			end->x = graphics->map->info->row_size;
			angle_diff -= M_PI / 4.0;
			angle_diff = (M_PI / 4.0) - angle_diff;
			end->y = ((start.x - end->x) * tan(angle_diff)) + start.y;
		}
		else
		{
			end->y = 1.0;
			end->x = ((start.y - end->y) * tan(angle_diff)) + start.x;
		}
	}
}

static void set_north_west(t_ray_vars *vars, double angle)
{
	if ((angle >= M_PI / 2.0) && angle <= ((3 * M_PI)/2.0))
		vars->west = 0;
	else
		vars->west = 1;
	if ((angle <= M_PI) && angle >= 0)
		vars->north = 1;
	else
		vars->north = 0;
}

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

static void dda_starting_conditions(t_dda_vars *dvars)
{
	if (dvars->dx < 0)
	{
		dvars->x = -1;
		dvars->sidelen_x = (dvars->start.x - (double)dvars->map_x) * dvars->x_step;
	}
	else
	{
		dvars->x = 1;
		dvars->sidelen_x = (((double)(dvars->map_x + 1.0)) - dvars->start.x) * dvars->x_step;
	}
	if (dvars->dy < 0)
	{
		dvars->y = -1;
		dvars->sidelen_y = (dvars->start.y - (double)dvars->map_y) * dvars->y_step;
	}
	else
	{
		dvars->y = 1;
		dvars->sidelen_y = (((double)(dvars->map_y + 1.0)) - dvars->start.y) * dvars->y_step;
	}
}

static void dda_init(t_dda_vars *dvars)
{
	dvars->dx = (dvars->end.x - dvars->start.x);
	dvars->dy = (dvars->end.y - dvars->start.y);
	if (dvars->dx == 0)
		dvars->x_step = 1e30;
	else
		dvars->x_step = sqrt(1 + ((dvars->dy / dvars->dx) * (dvars->dy / dvars->dx)));
	if (dvars->dy == 0)
		dvars->y_step = 1e30;
	else
		dvars->y_step = sqrt(1 + ((dvars->dx / dvars->dy) * (dvars->dx / dvars->dy)));
	dvars->map_x = (int)dvars->start.x;
	dvars->map_y = (int)dvars->start.y;
	dda_starting_conditions(dvars);
	dvars->curr_pos.x = dvars->start.x;
	dvars->curr_pos.y = dvars->start.y;
	dvars->ray_x = dvars->start.x;
	dvars->ray_y = dvars->start.y;
}

static void dda_increment(t_dda_vars *dvars)
{
	if (dvars->sidelen_x < dvars->sidelen_y)
	{
		dvars->end_distance = dvars->sidelen_x;
		dvars->sidelen_x += dvars->x_step;
		dvars->map_x += dvars->x;
		dvars->ray_x += dvars->x;
		dvars->last_move = 1;
	}
	else
	{
		dvars->end_distance = dvars->sidelen_y;
		dvars->sidelen_y += dvars->y_step;
		dvars->map_y += dvars->y;
		dvars->ray_y += dvars->y;
		dvars->last_move = 2;
	}
}

static void perform_dda(t_ray_vars *rvars, t_dda_vars *dvars, int **grid)
{
	dda_init(dvars);
	while (1)
	{
		dda_increment(dvars);
		if (grid[dvars->map_y][dvars->map_x] == 1)
		{
			dvars->curr_pos.x = dvars->map_x * BLOCK_SIZE;
			dvars->curr_pos.y = dvars->map_y * BLOCK_SIZE;
			break ;
		}
	}
	rvars->dist = dvars->end_distance;
}


static void	set_ray_vars(t_graphics *graphics, double angle, t_ray_vars *vars)
{
	t_dda_vars	dvars;
	t_player	*player;

	player = graphics->player;
	dvars.start.x = player->position.x / BLOCK_SIZE;
	dvars.start.y = player->position.y / BLOCK_SIZE;
	set_north_west(vars, angle);
	set_endpoint(graphics, &(dvars.end), dvars.start, angle);
	perform_dda(vars, &dvars, graphics->map->grid);
	double current_angle = player->angle - angle;
	if (dvars.last_move == 2)
	{
		if (vars->north)
			vars->t_sel = NORTH;
		else
			vars->t_sel = SOUTH;
		vars->depth = cos(angle) * dvars.end_distance + dvars.start.x;
	}
	else
	{
		if (vars->west)
			vars->t_sel = WEST;
		else
			vars->t_sel = EAST;
		vars->depth = sin(angle) * dvars.end_distance + dvars.start.y;
	}
	vars->depth -= floor(vars->depth);
	if (current_angle < 0)
	  current_angle += 2 * M_PI;
	if (current_angle > 2 * M_PI)
	  current_angle -= 2 * M_PI;
	vars->dist = vars->dist * cos(current_angle);
}
uint32_t rgbaToInteger(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return (r << 24) | (g << 16) | (b << 8) | a;
}

int	mlx_pixel_get(mlx_texture_t *texture, int texture_index_x, int texture_index_y)
{
	unsigned char	rgba[4];
	int				t;

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

void	paint_ceiling_floor(t_graphics *graphics)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			if (j > WINDOW_HEIGHT / 2)
				mlx_put_pixel(graphics->map->img, i, j, graphics->ceiling_color);
			else
				mlx_put_pixel(graphics->map->img, i, j, graphics->floor_color);
			j++;
		}
		i++;
	}
}

void	ray(t_graphics *graphics)
{
	t_ray_vars		vars;
	double			left_angle;
	double			current_angle;
	double			step_size;
	double			max_wall_size;
	int				pixels_to_draw;
	unsigned char 	color[4];

	paint_ceiling_floor(graphics);
	step_size = (0.001171875 * (640.0 / WINDOW_WIDTH));
	left_angle = graphics->player->angle - ((step_size * WINDOW_WIDTH) / 2);
	current_angle = left_angle;
	for (int i = 0; i < WINDOW_WIDTH; i++)
	{
		if (current_angle < 0)
		  current_angle += 2 * M_PI;
		if (current_angle > 2 * M_PI)
		  current_angle -= 2 * M_PI;
		set_ray_vars(graphics, current_angle, &vars);
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
				int texture_index_y = test * ((double)graphics->texture_w->height/ (double)(pixels_to_draw));
				mlx_put_pixel(graphics->map->img, i, j, mlx_pixel_get(graphics->texture_w, texture_index_x, texture_index_y));
			}
			else if (vars.t_sel == NORTH)
			{
				int texture_index_y = test * ((double)graphics->texture_n->height/ (double)(pixels_to_draw));
				mlx_put_pixel(graphics->map->img, i, j, mlx_pixel_get(graphics->texture_n, texture_index_x, texture_index_y));
			}
			else if (vars.t_sel == SOUTH)
			{
				int texture_index_y = test * ((double)graphics->texture_s->height/ (double)(pixels_to_draw));
				mlx_put_pixel(graphics->map->img, i, j, mlx_pixel_get(graphics->texture_s, texture_index_x, texture_index_y));
			}
			else
			{
				int texture_index_y = test * ((double)graphics->texture_e->height/ (double)(pixels_to_draw));
				mlx_put_pixel(graphics->map->img, i, j, mlx_pixel_get(graphics->texture_e, texture_index_x, texture_index_y));
			}
			test++;
		}
		current_angle += step_size;
	}
}
