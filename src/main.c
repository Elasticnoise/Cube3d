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