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

void	load_image(t_img *img, void *mlx_ptr, char *path)
{
	if (!ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4))
		img->img = mlx_xpm_file_to_image(mlx_ptr, path,
										 &img->img_width, &img->img_height);
	if (!img->img)
	{
//		error_message("Error : ");
//		error_message(path);
//		error_message(" : No such image or format error\n");
		exit(EXIT_FAILURE);
	}
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel,
										 &img->size_l, &img->endian);
}

void	save_image(t_all *all, int **text, char *path, t_img *img)
{
	int		x;
	int		y;

	y = 0;
	x = 0;
	load_image(img, all->win->mlx, path);
	*text = malloc(sizeof(int) * TXTR_H * TXTR_W);
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			(*text)[img->img_width * y + x] = img->addr[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(all->win->mlx, img->img);
}

void	floor_ceiling(t_all *all)
{
	int	y;
	int	x;
	int	ceiling;
	int	floor;

	floor = create_trgb(
			all->map->floor.R,
			all->map->floor.G,
			all->map->floor.B);
	ceiling = create_trgb(
			all->map->ceil.R,
			all->map->ceil.G,
			all->map->ceil.B);
	y = WIN_Y / 2 - 1;
	while (y < WIN_Y)
	{
		x = -1;
		while (++x < WIN_X)
		{
			all->buff[WIN_Y - y - 1][x] = ceiling;
			all->buff[y][x] = floor;
		}
		y++;
	}
}

void	calc_step_and_dist(t_all *all)
{
	if (all->plr->ray_dir_x < 0)
	{
		all->plr->step_x = -1;
		all->plr->side_dist_x = (all->plr->x - all->plr->map_x)
							 * all->plr->delta_dist_x;
	}
	else
	{
		all->plr->step_x = 1;
		all->plr->side_dist_x = (all->plr->map_x + 1.0 - all->plr->x)
							 * all->plr->delta_dist_x;
	}
	if (all->plr->ray_dir_y < 0)
	{
		all->plr->step_y = -1;
		all->plr->side_dist_y = (all->plr->y - all->plr->map_y)
							 * all->plr->delta_dist_y;
	}
	else
	{
		all->plr->step_y = 1;
		all->plr->side_dist_y = (all->plr->map_y + 1.0 - all->plr->y)
							 * all->plr->delta_dist_y;
	}
}

void	digital_differential_analyzer(t_all *all)
{
	while (all->plr->hit == 0)
	{
		if (all->plr->side_dist_x < all->plr->side_dist_y)
		{
			all->plr->side_dist_x += all->plr->delta_dist_x;
			all->plr->map_x += all->plr->step_x;
			all->plr->side = 0;
		}
		else
		{
			all->plr->side_dist_y += all->plr->delta_dist_y;
			all->plr->map_y += all->plr->step_y;
			all->plr->side = 1;
		}
		if (all->plr->map[all->plr->map_x][all->plr->map_y] == 1)
			all->plr->hit = 1;
	}
	if (all->plr->side == 0)
		all->plr->perp_wall_dist = (all->plr->map_x - all->plr->x
								 + (1 - all->plr->step_x) / 2) / all->plr->ray_dir_x;
	else
		all->plr->perp_wall_dist = (all->plr->map_y - all->plr->y
								 + (1 - all->plr->step_y) / 2) / all->plr->ray_dir_y;
}

void	calc_height_and_dist_of(t_all *all)
{
	all->plr->line_height = (int)(WIN_Y / all->plr->perp_wall_dist);
	all->plr->draw_start = -all->plr->line_height / 2 + WIN_Y / 2;
	if (all->plr->draw_start < 0)
		all->plr->draw_start = 0;
	all->plr->draw_end = all->plr->line_height / 2 + WIN_Y / 2;
	if (all->plr->draw_end >= WIN_Y)
		all->plr->draw_end = WIN_Y - 1;
}

void	choose_textures_color(t_all *all)
{
	if (all->plr->side == 1 && all->plr->ray_dir_y < 0)
		all->plr->txtr_num = 3;
	else if (all->plr->side == 1 && all->plr->ray_dir_y >= 0)
		all->plr->txtr_num = 2;
	else if (all->plr->side == 0 && all->plr->ray_dir_x <= 0)
		all->plr->txtr_num = 0;
	else if (all->plr->side == 0 && all->plr->ray_dir_x > 0)
		all->plr->txtr_num = 1;
	else if (all->plr->map[all->plr->map_y][all->plr->map_x] == 'D')
		all->plr->txtr_num = 4;
	else
		all->plr->txtr_num = all->plr->map[all->plr->map_y][all->plr->map_x];
}

void	calc_ray_position_direction(t_all *all, int x)
{
	all->plr->camera_x = 2 * x / (double)WIN_X - 1;
	all->plr->ray_dir_x = all->plr->x + all->plr->plane_x * all->plr->camera_x;
	all->plr->ray_dir_y = all->plr->y + all->plr->plane_y * all->plr->camera_x;
	all->plr->map_x = (int)all->plr->x;
	all->plr->map_y = (int)all->plr->y;
	all->plr->delta_dist_x = fabs(1 / all->plr->ray_dir_x);
	all->plr->delta_dist_y = fabs(1 / all->plr->ray_dir_y);
	all->plr->hit = 0;
}

void	calculate_value_of_wall_x(t_all *all)
{
	if (all->plr->side == 0)
		all->plr->wall_x = all->plr->y + all->plr->perp_wall_dist * all->plr->ray_dir_y;
	else
		all->plr->wall_x = all->plr->x + all->plr->perp_wall_dist * all->plr->ray_dir_x;
	all->plr->wall_x -= floor(all->plr->wall_x);
	all->plr->txtr_x = (int)(all->plr->wall_x * (double)TXTR_W);
	if (all->plr->side == 0 && all->plr->ray_dir_x > 0)
		all->plr->txtr_x = TXTR_W - all->plr->txtr_x - 1;
	if (all->plr->side == 1 && all->plr->ray_dir_y < 0)
		all->plr->txtr_x = TXTR_W - all->plr->txtr_x - 1;
	all->plr->step = 1.0 * TXTR_H / all->plr->line_height;
	all->plr->txtr_pos = (all->plr->draw_start - WIN_Y / 2
					   + all->plr->line_height / 2) * all->plr->step;
}

void	draw_wall_textures(t_all *all, int x)
{
	int	y;

	y = all->plr->draw_start;
	while (y < all->plr->draw_end)
	{
		all->plr->txtr_y = (int)all->plr->txtr_pos & (TXTR_H - 1);
		all->plr->txtr_pos += all->plr->step;
		all->plr->color = all->textures[all->plr->txtr_num][TXTR_H * all->plr->txtr_y
													+ all->plr->txtr_x];
		if (all->plr->side == 1)
			all->plr->color = (all->plr->color >> 1) & 8355711;
		all->buff[y][x] = all->plr->color;
		y++;
	}
}

void	walls(t_all *all)
{
	int	x;

	(void)all;
	x = 0;
	while (x < WIN_X)
	{
		calc_ray_position_direction(all, x);
		calc_step_and_dist(all);
		digital_differential_analyzer(all);
		calc_height_and_dist_of(all);
		choose_textures_color(all);
		calculate_value_of_wall_x(all);
		draw_wall_textures(all, x);
		all->plr->z_buffer[x] = all->plr->perp_wall_dist;
		x++;
	}
}

//void	key_update(t_all *all)
//{
//	if (all->key[W])
//		move_straight(all);
//	if (all->key[S])
//		move_back(all);
//	if (all->key[D])
//		move_to_right(all);
//	if (all->key[A])
//		move_to_left(all);
//	if (all->key_r)
//		rotate_screen_to_right(all);
//	if (all->key_l)
//		rotate_screen_to_left(all);
//}

void	draw_buff(t_all *all)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			all->mlx_image->addr[y * WIN_X + x] = all->buff[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(all->win->mlx, all->win->mlx,
							all->mlx_image->img, 0, 0);
}

int	action(t_all *all)
{
	all->curr_time++;
	if (all->curr_time == LONG_MAX)
		all->curr_time = 0;
	floor_ceiling(all);
	walls(all);
//	textures(all);
	key_update(all);
	draw_buff(all);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_map	map;
	t_all	all;
	t_win	win;
	t_plr	plr;
	t_img	img;

	errno = 0;
	if (argc != 2)
        error_msg("Not correct number of arguments\n");
    check_map(argv[1], &map);
	all.map = &map;
	find_unit(&plr, all.map->my_map);
	all.plr = &plr;
	printf("%f x %f y BEGIN\n", all.plr->x, all.plr->y);
	win.mlx = mlx_init();
//	win.mlx_win = mlx_new_window(win.mlx, WIN_X, WIN_Y, "Cub3D");
	all.win->mlx = mlx_new_window(all.win->mlx, WIN_X, WIN_Y, "Cub3D");
	all.mlx_image = malloc(sizeof(t_img));
	all.mlx_image->img = mlx_new_image(all.win->mlx, WIN_X, WIN_Y);
	all.mlx_image->addr = (int *)mlx_get_data_addr(\
			all.mlx_image->img,
			&all.mlx_image->bits_per_pixel,
			&all.mlx_image->line_length,
			&all.mlx_image->endian);
//	win.img = mlx_new_image(win.mlx, 620, 480);
	win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.line_l, &win.en);
//	pixel_put(&win, 20, 20, 0xFFFFF);
//	mlx_put_image_to_window(win.mlx, win.mlx_win, win.img, 0, 0);
//	mlx_loop(win.mlx);
	all.win = &win;
	draw(&all);
//	save_image(&all, &all.textures, "textures/wall_0.png", &img);
	mlx_hook(win.mlx_win, 2, (1L << 0), &key_hook, &all);
	mlx_loop_hook(win.mlx_win, action, &all);
//	mlx_hook(win.mlx_win, 17, 0, close_hook, &/all);
//	mlx_key_hook(win.mlx_win, key_hook, &all);
//	mlx_hook(win.win, 2, (1L << 0),  );
//	mlx_put_image_to_window(all.win->mlx, all.win->mlx_win, all.win->img, 0,0);
	mlx_loop(win.mlx);
    return (0);
}