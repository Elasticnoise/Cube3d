#include "../../includes/cube3d.h"

void	move_to_left(t_all *all)
{
	int	next_x;
	int	next_y;

	next_x = (int)(all->plr->x - all->plr->plane_x * all->plr->move_speed);
	next_y = (int)(all->plr->y - all->plr->plane_y * all->plr->move_speed);
	if (!all->plr->map[next_x][next_y])
	{
		all->plr->x -= all->plr->plane_x * all->plr->move_speed;
		all->plr->y -= all->plr->plane_y * all->plr->move_speed;
	}
}

void	key_update(t_all *all)
{
	if (all->key[W])
		move_straight(all);
	if (all->key[S])
		move_back(all);
	if (all->key[D])
		move_to_right(all);
	if (all->key[A])
		move_to_left(all);
	if (all->key_r)
		rotate_screen_to_right(all);
	if (all->key_l)
		rotate_screen_to_left(all);
}
