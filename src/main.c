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

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

//void	ft_cast_ray(t_all *all)
//{
//	t_plr	ray = (*all).plr; // задаем координаты луча равные координатам
//	// игрока
//
//	while ((*all).map->my_map[(int)(ray.y / SIZE)][(int)(ray.x / SIZE)] != '1')
//	{
//		ray.x += cos((int)ray.dir);
//		ray.y += sin((int)ray.dir);
//		mlx_pixel_put((*all).win.mlx, (*all).win.mlx_win, ray.x, ray.y,
//				0x990099);
//	}
//}


void	pixel_put(t_win *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_l + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	scale(t_win *win, int color, int x1, int y1)
{
	int x = (x1 + 1) * SIZE;
	int y = (y1 + 1) * SIZE;
	x1 *= SIZE;
	y1 *= SIZE;
	while (y1 < y)
	{
		while (x1 < x)
		{
//			mlx_pixel_put(win->mlx, win->mlx_win, x1++, y1, color);
			pixel_put(win, x1++, y1, color);
		}
		x1 -= SIZE;
		y1++;
	}
}

void	draw(t_all *all)
{
	int x = 0, y = 0;
	t_win *win = all->win;

	printf("%f x %f y DRAW\n", all->plr->x, all->plr->y);
	win->img = mlx_new_image(win->mlx, 620, 480);
	win->addr = mlx_get_data_addr(win->img, &win->bpp, &win->line_l, &win->en);
	while (all->map->my_map[y])
	{
		x = 0;
//		printf("%s\n", all->map->my_map[y]);
		while (all->map->my_map[y][x])
		{
			if (all->map->my_map[y][x] == '1')
				scale(all->win, 0xFFFFFF, x, y);
			x++;
		}
		y++;
	}
	draw_player(all, all->plr);
//	scale(all->win, 0xFF0000, (int)(all->plr->x / SIZE), (int)(all->plr->y /
//	SIZE));
	mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0,0);
	mlx_destroy_image(all->win->mlx, all->win->img);
}

void draw_player(t_all *all, t_plr *pl)
{
	t_plr	plr = *all->plr;

	plr.start = plr.dir - M_PI_4;
	plr.end = plr.dir + M_PI_4;
	printf("%d and %d  sadsadas\n", (int) (plr.y / SIZE), (int) (plr.x / SIZE));
	while (plr.start < plr.end)
	{
		plr.x = pl->x;
		plr.y = pl->y;
		while (all->map->my_map[(int) (plr.y / SIZE)][(int) (plr.x / SIZE)] !=
			   '1')
		{

			plr.x += cos(plr.start);
			plr.y += sin(plr.start);
			pixel_put(all->win, plr.x, plr.y, GC);
		}
		plr.start += M_PI_2 / 640;
	}
}

void	find_unit(t_plr	*plr, char **my_map)
{
	int		i;
	int		j;

	i = 0;
	plr->dir = 3 * M_PI_2;
	while (my_map[i])
	{
		j = 0;
		while (my_map[i][j])
		{
			if (check_char(my_map[i][j]) == CORR_CHAR)
			{
				plr->x = (float) j * SIZE;
				plr->y = (float) i * SIZE;
			}
			j++;
		}
		i++;
	}
}

int	close_hook(t_all *all)
{
	(void)all;
	exit (0);
}

int	key_hook(int keycode, t_all *all)
{
	(void) all;
	(void) keycode;
	mlx_clear_window(all->win->mlx, all->win->mlx_win);

//	if (keycode == 53)
//	{
//		mlx_destroy_window(all->win->mlx, all->win->mlx_win);
//		free_array(all->map->my_map);
//		exit(0);
//	}
//	actions(keycode, (int)all->plr->x, (int)all->plr->y, all);
	if (keycode == 13 || keycode == 126)
	{
		all->plr->x += cos(all->plr->dir) * 4;
//		all->plr->y -= 1;
		all->plr->y += sin(all->plr->dir) * 4;
	}
	if (keycode == 1 || keycode == 125)
	{
		all->plr->x -= cos(all->plr->dir) * 4;
//		all->plr->y += 1;
		all->plr->y -= sin(all->plr->dir) * 4;
	}
	if (keycode == 0 || keycode == 123)
//		all->plr->x -= 1;
		all->plr->dir -= 0.1;
	if (keycode == 2 || keycode == 124)
//		all->plr->x += 1;
		all->plr->dir += 0.1;
	if (keycode == 53)
		exit(0);
	draw(all);
//	draw_player(all, all->plr);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_map	map;
	t_all	all;
	t_win	win;
	t_plr	plr;

	errno = 0;
	if (argc != 2)
        error_msg("Not correct number of arguments\n");
    check_map(argv[1], &map);
	all.map = &map;
	find_unit(&plr, all.map->my_map);
	all.plr = &plr;
	printf("%f x %f y BEGIN\n", all.plr->x, all.plr->y);
	win.mlx = mlx_init();
	win.mlx_win = mlx_new_window(win.mlx, 620, 480, "Cub3D");
	win.img = mlx_new_image(win.mlx, 620, 480);
	win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.line_l, &win.en);
//	pixel_put(&win, 20, 20, 0xFFFFF);
//	mlx_put_image_to_window(win.mlx, win.mlx_win, win.img, 0, 0);
//	mlx_loop(win.mlx);
	all.win = &win;
	draw(&all);
	mlx_hook(win.mlx_win, 2, (1L << 0), &key_hook, &all);
//	mlx_hook(win.mlx_win, 17, 0, close_hook, &/all);
//	mlx_key_hook(win.mlx_win, key_hook, &all);
//	mlx_hook(win.win, 2, (1L << 0),  );
//	mlx_put_image_to_window(all.win->mlx, all.win->mlx_win, all.win->img, 0,0);
	mlx_loop(win.mlx);
    return (0);
}