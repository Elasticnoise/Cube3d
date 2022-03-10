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


//void	pixel_put(t_win *data, int x, int y, int color)
//{
//	char	*dst;
//
//	dst = data->addr + (y * data->line_l + x * (data->bpp / 8));
//	*(unsigned int*)dst = color;
//}
//
//void	scale(t_win *win, int color, int x1, int y1)
//{
//	int x = (x1 + 1) * SIZE;
//	int y = (y1 + 1) * SIZE;
//	x1 *= SIZE;
//	y1 *= SIZE;
//	while (y1 < y)
//	{
//		while (x1 < x)
//		{
////			mlx_pixel_put(win->mlx, win->mlx_win, x1++, y1, color);
//			pixel_put(win, x1++, y1, color);
//		}
//		x1 -= SIZE;
//		y1++;
//	}
//}
//
//void	draw(t_all *all)
//{
//	int x = 0, y = 0;
////	t_win *win = all->win;
//
//	printf("%f x %f y DRAW\n", all->plr->x, all->plr->y);
////	win->img = mlx_new_image(win->mlx, 620, 480);
////	win->addr = mlx_get_data_addr(win->img, &win->bpp, &win->line_l, &win->en);
//	while (all->map->my_map[y])
//	{
//		x = 0;
////		printf("%s\n", all->map->my_map[y]);
//		while (all->map->my_map[y][x])
//		{
//			if (all->map->my_map[y][x] == '1')
//				scale(all->win, 0xFFFFFF, x, y);
//			x++;
//		}
//		y++;
//	}
//	draw_player(all, all->plr);
////	scale(all->win, 0xFF0000, (int)(all->plr->x / SIZE), (int)(all->plr->y /
////	SIZE));
//	mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0,0);
////	mlx_destroy_image(all->win->mlx, all->win->img);
//}
//
//void draw_player(t_all *all, t_plr *pl)
//{
//	t_plr	plr = *all->plr;
//
//	int s;
//	s = 16;
//	plr.start = plr.dir - M_PI_4;
//	plr.end = plr.dir + M_PI_4;
////	all->win->img = mlx_xpm_file_to_image(all->win->mlx,
////										  "/Users/ghanh/Dev/Cube3d/texture/first.xpm", &s,
////										  &s);
//	printf("%d and %d  sadsadas\n", (int) (plr.y / SIZE), (int) (plr.x / SIZE));
////	mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, plr.x
////																			 * SIZE, plr.y * SIZE);
//	while (plr.start < plr.end)
//	{
//		plr.x = pl->x;
//		plr.y = pl->y;
//		while (all->map->my_map[(int) (plr.y / SIZE)][(int) (plr.x / SIZE)] !=
//			   '1')
//		{
//			plr.x += cos(plr.start);
//			plr.y += sin(plr.start);
////			pixel_put(all->win, plr.x, plr.y, GC);
//		}
//		printf("%d and %d  KEKS\n", (int) (plr.y), (int) (plr.x));
//		plr.start += M_PI_2 / 640;
//	}
//}



int	close_hook(t_all *all)
{
	(void)all;
	exit (0);
}

int		check_wall(t_all *all, float side_dir)
{
	int x;
	int y;

	x = all->player->x;
	y = all->player->y;
	x += 64 * cos(degrees_to_rad(side_dir));
	y += 64 * sin(degrees_to_rad(side_dir));
	if ((all->map->my_map)[y / 64][x / 64] == '1')
		return (0);
	return (1);
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
	double side_dir;

	if (keycode == 53)
		exit(0);
	rotate(keycode, all->player);
//	side_dir = normalize_deg(all->plr->dir);
	if (keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2)
	{
		if (keycode == 1)
			side_dir = normalize_deg(all->player->dir - 180);
		else if (keycode == 13)
			side_dir = all->player->dir;
		if (check_wall(all, side_dir))
		{
			all->player->x += 8 * cos(degrees_to_rad(side_dir)); //TODO STEP OR SIZE
			all->player->y += 8 * sin(degrees_to_rad(side_dir));//TODO STEP OR SIZE
		}
	}
	raycaster(all);
	mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0, 0);
	return (0);
}

static void	text_help(t_texture *text, char *path, t_all *all)
{
	text->img = mlx_xpm_file_to_image(all->win->mlx, path,
									&text->width, &text->height);
	if (!text->img)
		error_msg("Incorrect textures path ");
	text->addr = mlx_get_data_addr(text->img, &text->bits_per_pixel,
								   &text->line_length, &text->endian);
}

void	textures_init(t_all *all)
{
	all->map->texture = malloc(sizeof(t_texture) * NUM_OF_TEXT);
	if (!all->map->texture)
		error_msg("Malloc failed\n");
	text_help(&(all->map->texture[SOUTH]), all->map->south, all);
	text_help(&(all->map->texture[NORTH]), all->map->north, all);
	text_help(&(all->map->texture[WEST]), all->map->west, all);
	text_help(&(all->map->texture[EAST]), all->map->east, all);
}


int		rgb_to_int(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16) | (g << 8) | b;
}

int	main(int argc, char *argv[])
{
	t_map	map;
	t_all	all;
	t_win	win;
	t_plr	plr;
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
	all.floor_color = rgb_to_int(map.floor.R, map.floor.G, map.floor.B);
	all.ceil_color = rgb_to_int(map.ceil.R, map.ceil.G, map.ceil.B);
//	printf("%f x %f y BEGIN\n", all.plr->x, all.plr->y);
	all.win = &win;

	all.win->mlx_win = mlx_new_window(	all.win->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	all.win->img = mlx_new_image(	all.win->mlx, WIN_WIDTH, WIN_HEIGHT);
	all.win->addr = mlx_get_data_addr(all.win->img, &all.win->bpp, &all.win->line_l, &all.win->en);
	textures_init(&all);
//	draw(&all);  //// 2D map
	raycaster(&all);
	mlx_put_image_to_window(all.win->mlx, all.win->mlx_win, all.win->img,
							0,0);
	mlx_hook(all.win->mlx_win, 2, (1L << 0), &key_hook, &all);;
	mlx_loop(all.win->mlx);
    return (0);
}