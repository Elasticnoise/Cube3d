/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:07:09 by lechalme          #+#    #+#             */
/*   Updated: 2022/03/11 21:07:10 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	check_wall(t_all *all, float side_dir)
{
	int	x;
	int	y;

	x = all->player->x;
	y = all->player->y;
	x += 64 * cos(degrees_to_rad(side_dir));
	y += 64 * sin(degrees_to_rad(side_dir));
	if ((all->map->my_map)[y / 64][x / 64] == '1')
		return (0);
	return (1);
}

void	text_help(t_texture *text, char *path, t_all *all)
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
