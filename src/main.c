#include "cube3d.h"

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
			mlx_pixel_put(win->mlx, win->mlx_win, x1++, y1, color);
		}
		x1 -= SIZE;
		y1++;
	}
}

void	draw(t_all *all)
{
	int x = 0, y = 0;

	while (all->map->my_map[y])
	{
		x = 0;
		printf("%s\n", all->map->my_map[y]);
		while (all->map->my_map[y][x])
		{
			if (all->map->my_map[y][x] == '1')
				scale(all->win, 0xFFFFFF, x, y);
			x++;
		}
		y++;
	}
}

int	main(int argc, char *argv[])
{
	t_map	map;
	t_all	all;
	t_win	win;

	errno = 0;
	if (argc != 2)
        error_msg("Not correct number of arguments\n");
    check_map(argv[1], &map);
	all.map = &map;
	win.mlx = mlx_init();
	win.mlx_win = mlx_new_window(win.mlx, 620, 480, "Cub3D");
	win.img = mlx_new_image(win.mlx, 620, 480);
	win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.line_l, &win.en);
//	pixel_put(&win, 20, 20, 0xFFFFF);
//	mlx_put_image_to_window(win.mlx, win.mlx_win, win.img, 0, 0);
//	mlx_loop(win.mlx);
	all.win = &win;

	draw(&all);
//	mlx_hook(win.win, 2, (1L << 0),  );
	mlx_loop(all.win->mlx);
    return (0);
}