/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_deg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:06:59 by lechalme          #+#    #+#             */
/*   Updated: 2022/03/11 21:07:00 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cube3d.h"

int	is_looking_up(float deg)
{
	if (deg > 180)
		return (1);
	else
		return (-1);
}

float	normalize_deg(float deg)
{
	if (deg < 0)
		return (360 + deg);
	if (deg > 360)
		return (deg - 360);
	return (deg);
}

int	is_looking_right(float deg)
{
	if (deg < 90 || deg > 270)
		return (1);
	else
		return (-1);
}

double	degrees_to_rad(double degrees)
{
	return (degrees * (M_PI / 180));
}

float	intersection_detector(t_all *all, t_plr *ray, float distance)
{
	while (ray->map_x >= 0 && ray->map_y >= 0
		&& ray->map_x < all->map->width && ray->map_y < all->map->height)
	{
		if ((all->map->my_map)[ray->map_y][ray->map_x] == '1')
		{
			distance = get_vector_length(all, *ray);
			break ;
		}
		ray->x += ray->delta_x;
		ray->y += ray->delta_y;
		ray->map_x = ((int)(ray->x / 64));
		ray->map_y = ((int)(ray->y / 64));
	}
	return (distance);
}
