#include "../../includes/cube3d.h"

float	vertical_tracing(t_all *game, double deg, t_plr *ray)
{
	float	distance;

	distance = MAXFLOAT;
	if (is_looking_right(deg) == 1)
		ray->delta_x = 64;
	else
		ray->delta_x = -64;
	if (deg == 90 || deg == 270)
		return (distance);
	if (is_looking_right(deg) == 1)
		ray->x = (int)((game->player->x / 64) * 64) + 64;
	else
		ray->x = (int)((game->player->x / 64) * 64) + (-0.001);
	ray->y = game->player->y + (game->player->x - ray->x)
		* tan(degrees_to_rad(deg)) * (-1);
	ray->delta_y = ray->delta_x * tan(degrees_to_rad(deg));
	ray->map_x = ((int)(ray->x / 64));
	ray->map_y = ((int)(ray->y / 64));
	distance = intersection_detector(game, ray, distance);
	return (distance);
}

float	horizontal_tracing(t_all *game, double deg, t_plr *ray)
{
	float	distance;

	distance = MAXFLOAT;
	if (is_looking_up(deg) == 1)
		ray->delta_y = -1;
	else
		ray->delta_y = 1;
	if (deg == 0 || deg == 180 || deg == 360)
		return (distance);
	if (is_looking_up(deg) == 1)
		ray->y = (int)((game->player->y / 64) * 64) + (-0.001);
	else
		ray->y = (int)((game->player->y / 64) * 64) + 64;
	ray->x = game->player->x + (game->player->y - ray->y)
		/ tan(degrees_to_rad(deg)) * (-1);
	ray->delta_x = ray->delta_y / tan(degrees_to_rad(deg));
	ray->map_x = ((int)(ray->x / 64));
	ray->map_y = ((int)(ray->y / 64));
	distance = intersection_detector(game, ray, distance);
	return (distance);
}
