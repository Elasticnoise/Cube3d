#include "../../includes/cube3d.h"

void	north_or_south_wall(t_plr *result, t_plr ray, float dist, float deg)
{
	result->x = ray.x;
	result->y = ray.y;
	if (is_looking_up(deg) == 1)
		result->wall = NORTH;
	else
		result->wall = SOUTH;
	result->length = dist;
}

void	west_or_east_wall(t_plr *result, t_plr ray, float dist, float deg)
{
	result->x = ray.x;
	result->y = ray.y;
	if (is_looking_right(deg) == 1)
		result->wall = EAST;
	else
		result->wall = WEST;
	result->length = dist;
}

