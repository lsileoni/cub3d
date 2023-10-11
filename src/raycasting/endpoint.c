/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endpoint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:26:00 by lsileoni          #+#    #+#             */
/*   Updated: 2023/10/10 20:53:01 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "graphics.h"

static void	north_east(t_graphics *graphics, double angle,
		t_point *end, t_point start)
{
	double	angle_diff;

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

static void	north_west(t_graphics *graphics, double angle,
		t_point *end, t_point start)
{
	double	angle_diff;

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

static void	south_west(double angle, t_point *end, t_point start)
{
	double	angle_diff;

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

static void	south_east(t_graphics *graphics, double angle,
		t_point *end, t_point start)
{
	double	angle_diff;

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

void	set_endpoint(t_graphics *graphics, t_point *end,
		t_point start, double angle)
{
	if (angle < (((M_PI * 3) / 2.0) + 0.00001) && \
			angle > (((M_PI * 3) / 2.0) - 0.00001))
	{
		end->y = 1.0;
		end->x = start.x + 0.125;
	}
	else if (angle > 0.0 && angle <= M_PI / 2.0)
		north_east(graphics, angle, end, start);
	else if (angle > M_PI / 2.0 && angle <= M_PI)
		north_west(graphics, angle, end, start);
	else if (angle > M_PI && angle <= (3.0 * M_PI) / 2.0)
		south_west(angle, end, start);
	else
		south_east(graphics, angle, end, start);
}
