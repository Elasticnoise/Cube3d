#include "../../includes/cube3d.h"

void	rotate_screen_to_right(t_all *all)
{
	double	old_dir_x;
	double	old_plane_x;

	old_plane_x = all->plr->plane_x;
	old_dir_x = all->plr->ray_dir_x;
	all->plr->ray_dir_x = all->plr->ray_dir_x * cos(-all->plr->rot_speed)
		- all->plr->ray_dir_y * sin(-all->plr->rot_speed);
	all->plr->ray_dir_y = old_dir_x * sin(-all->plr->rot_speed)
		+ all->plr->ray_dir_y * cos(-all->plr->rot_speed);
	all->plr->plane_x = all->plr->plane_x * cos(-all->plr->rot_speed)
		- all->plr->plane_y * sin(-all->plr->rot_speed);
	all->plr->plane_y = old_plane_x * sin(-all->plr->rot_speed)
		+ all->plr->plane_y * cos(-all->plr->rot_speed);
}

void	rotate_screen_to_left(t_all *all)
{
	double	old_dir_x;
	double	old_plane_x;

	old_plane_x = all->plr->plane_x;
	old_dir_x = all->plr->ray_dir_x;
	all->plr->ray_dir_x = all->plr->ray_dir_x * cos(all->plr->rot_speed)
		- all->plr->delta_dist_y * sin(all->plr->rot_speed);
	all->plr->delta_dist_y = old_dir_x * sin(all->plr->rot_speed)
		+ all->plr->delta_dist_y * cos(all->plr->rot_speed);
	all->plr->plane_x = all->plr->plane_x * cos(all->plr->rot_speed)
		- all->plr->plane_y * sin(all->plr->rot_speed);
	all->plr->plane_y = old_plane_x * sin(all->plr->rot_speed)
		+ all->plr->plane_y * cos(all->plr->rot_speed);
}

void	move_straight(t_all *all)
{
	int	next_x;
	int	next_y;

	next_x = (int)(all->plr->x + all->plr->ray_dir_x * all->plr->move_speed);
	next_y = (int)(all->plr->y + all->plr->delta_dist_y * all->plr->move_speed);
	if (!all->plr->map[next_x][next_y])
	{
		all->plr->x += all->plr->ray_dir_x * all->plr->move_speed;
		all->plr->y += all->plr->delta_dist_y * all->plr->move_speed;
	}
}

void	move_back(t_all *all)
{
	int	next_x;
	int	next_y;

	next_x = (int)(all->plr->x - all->plr->ray_dir_x * all->plr->move_speed);
	next_y = (int)(all->plr->y - all->plr->delta_dist_y * all->plr->move_speed);
	if (!all->plr->map[next_x][next_y])
	{
		all->plr->x -= all->plr->ray_dir_x * all->plr->move_speed;
		all->plr->y -= all->plr->delta_dist_y * all->plr->move_speed;
	}
}

void	move_to_right(t_all *all)
{
	int	next_x;
	int	next_y;

	next_x = (int)(all->plr->x + all->plr->plane_x * all->plr->move_speed);
	next_y = (int)(all->plr->y + all->plr->plane_y * all->plr->move_speed);
	if (!all->plr->map[next_x][next_y])
	{
		all->plr->x += all->plr->plane_x * all->plr->move_speed;
		all->plr->y += all->plr->plane_y * all->plr->move_speed;
	}
}
