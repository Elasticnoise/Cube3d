///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   keycode_actions.c                                  :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: lechalme <lechalme@student.21-school.ru>   +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2021/10/22 18:02:14 by lechalme          #+#    #+#             */
///*   Updated: 2021/10/24 16:32:51 by lechalme         ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//#include "../includes/cube3d.h"
//
//static void	go_left(int x, int y, t_all *all)
//{
//	if (all->map->my_map[x - 1][y] && all->map->my_map[x - 1][y] == '1')
//	{
////		check_tile(x - 1, y, all);
////		if (all->plr->prev_step_flag == 1)
////			all->map->my_map[x][y] = 'E';
////		else
////			all->map->my_map[x][y] = '0';
////		all->map->my_map[x - 1][y] = 'P';
//		all->plr->x = x - 1;
//	}
//}
//
//void	go_right(int x, int y, t_all *all)
//{
//	if (all->map->my_map[x + 1][y] && all->map->my_map[x + 1][y] != '1')
//	{
////		check_tile(x + 1, y, game);
////		if (game->prev_step_flag == 1)
////			game->z_matrix[x][y] = 'E';
////		else
////			game->z_matrix[x][y] = '0';
////		game->z_matrix[x + 1][y] = 'P';
//		all->plr->x = x + 1;
//	}
//}
//
//void	go_top(int x, int y, t_all *all)
//{
//	if (all->map->my_map[x][y - 1] && all->map->my_map[x][y - 1] != '1')
//	{
////		check_tile(x, y - 1, all);
////		if (all->plr->prev_step_flag == 1)
////			all->map->my_map[x][y] = 'E';
////		else
////			all->map->my_map[x][y] = '0';
////		all->map->my_map[x][y - 1] = 'P';
//		all->plr->y = y - 1;
//	}
//}
//
//void	go_bottom(int x, int y, t_all *all)
//{
//	if (all->map->my_map[x][y + 1] && all->map->my_map[x][y + 1] != '1')
//	{
////		check_tile(x, y + 1, all);
////		if (all->plr->prev_step_flag == 1)
////			all->map->my_map[x][y] = 'E';
////		else
////			all->map->my_map[x][y] = '0';
////		all->map->my_map[x][y - 1] = 'P';
//		all->plr->y = y + 1;
//	}
//}
//
//void	actions(int keycode, int x, int y, t_all *all)
//{
//	if (keycode == 13 || keycode == 126)
//		go_top(x, y, all);
//	if (keycode == 1 || keycode == 125)
//		go_bottom(x, y, all);
//	if (keycode == 0 || keycode == 123)
//		go_left(x, y, all);
//	if (keycode == 2 || keycode == 124)
//		go_right(x, y, all);
////	printf("%f", all->plr->x);
////	draw(all);
////	scale(all->win, 0xFF0000, (int)all->plr->x, (int)all->plr->y);
//}
