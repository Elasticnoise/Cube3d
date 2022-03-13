/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:05:09 by lechalme          #+#    #+#             */
/*   Updated: 2022/03/11 21:05:11 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	*free_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

int	close_hook(t_all *all)
{
	(void)all;
	exit (0);
}

void	rotate(int key, t_player *player)
{
	if (key == 2)
		player->dir = normalize_deg(player->dir + 10);
	if (key == 0)
		player->dir = normalize_deg(player->dir - 10);
}

int	key_hook(int keycode, t_all *all)
{
	double	side_dir;

	if (keycode == 53)
		exit(0);
	rotate(keycode, all->player);
	if (keycode == 13 || keycode == 1)
	{
		if (keycode == 1)
			side_dir = normalize_deg(all->player->dir - 180);
		else if (keycode == 13)
			side_dir = all->player->dir;
		if (check_wall(all, side_dir))
		{
			all->player->x += 8 * cos(degrees_to_rad(side_dir));
			all->player->y += 8 * sin(degrees_to_rad(side_dir));
		}
	}
	raycaster(all);
	mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0, 0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_map		map;
	t_all		all;
	t_win		win;
	t_plr		plr;
	t_player	player;

	errno = 0;
	if (argc != 2)
		error_msg("Not correct number of arguments\n");
	check_map(argv[1], &map);
	all.map = &map;
	find_unit(&player, all.map->my_map);
	all.plr = &plr;
	all.player = &player;
	win.mlx = mlx_init();
	all.floor_color = rgb_to_int(map.floor.r, map.floor.g, map.floor.b);
	all.ceil_color = rgb_to_int(map.ceil.r, map.ceil.g, map.ceil.b);
	all.win = &win;
	textures_init(&all);
	all.win->mlx_win = mlx_new_window(all.win->mlx, WIN_WIDTH,
			WIN_HEIGHT, "Cub3D");
	all.win->img = mlx_new_image(all.win->mlx, WIN_WIDTH, WIN_HEIGHT);
	all.win->addr = mlx_get_data_addr(all.win->img,
			&all.win->bpp, &all.win->line_l, &all.win->en);
	raycaster(&all);
	mlx_put_image_to_window(all.win->mlx, all.win->mlx_win, all.win->img, 0, 0);
	mlx_hook(all.win->mlx_win, 17, 0, close_hook, &all);
	mlx_hook(all.win->mlx_win, 2, (1L << 0), &key_hook, &all);
	mlx_loop(all.win->mlx);
	return (0);
}
