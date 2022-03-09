#include "../../includes/cube3d.h"

float	get_vector_length(t_all *game, t_plr ray)
{
	float delta_x;
	float delta_y;

	delta_x = ray.x - game->plr->x;
	delta_y = ray.y - game->plr->y;
	return (sqrt(delta_x * delta_x + delta_y * delta_y));
}

t_plr 	analize_ray(t_all *all, float deg)
{
	t_plr ray1;
	t_plr ray2;
	t_plr ray;
	float dv;
	float dh;

	dv = vertical_tracing(all, deg, &ray1);
	dh = horizontal_tracing(all, deg, &ray2);
	if (dh < dv)
		north_or_south_wall(&ray, ray2, dh, deg);
	else
		west_or_east_wall(&ray, ray1, dv, deg);
	ray.perp_length = ray.length
					  * cos(degrees_to_rad(deg - all->plr->dir));
	return (ray);
}
//
//void	find_texture_x(t_all *all, t_plr *ray)
//{
//	if (ray->wall == SOUTH || ray->wall == NORTH)
//	{
//		ray->wall_x = ray->x / 64;
//		ray->wall_x -= floor(ray->wall_x);
//	}
//	else
//	{
//		ray->wall_x = ray->y / 64;
//		ray->wall_x -= floor(ray->wall_x);
//	}
//	all->textures[ray->wall]->text_x = (int)
//			(ray->wall_x * all->textures[ray->wall]->width);
//	if (ray->wall == EAST || ray->wall == SOUTH)
//		all->textures[ray->wall]->text_x = all->textures[ray->wall]->width
//											- all->textures[ray->wall]->text_x - 1;
//}

//t_line	find_vertical_line(t_all *all, t_plr ray, int x_pos)
//{
//	t_line line;
//	double column_height;
//
//	column_height = WIN_HEIGHT * 64 / ray.perp_length;
//	line.column_height = column_height;
//	line.top = WIN_HEIGHT / 2 - column_height / 2;
//	if (line.top < 0)
//		line.top = 0;
//	line.bot = WIN_HEIGHT / 2 + column_height / 2;
//	if (line.bot > WIN_HEIGHT)
//		line.bot = WIN_HEIGHT;
//	line.x_pos = x_pos;
//	return (line);
//}

int		raycaster(t_all *all)
{
	float	deg;
	t_plr	ray;
	int		x_vert_line_pos;
	t_line	vert_line;

	deg = normalize_deg(all->plr->dir - 30);
	x_vert_line_pos = 0;
	while (x_vert_line_pos < WIN_WIDTH)
	{
		ray = analize_ray(all, deg);
//		find_texture_x(all, &ray);
//		vert_line = find_vertical_line(all, ray, x_vert_line_pos);
//		draw_line(all, ray, vert_line);
		x_vert_line_pos++;
		deg += ONE_RAY_ANGLE(60, WIN_WIDTH);
		deg = normalize_deg(deg);
	}
	return (1);
}