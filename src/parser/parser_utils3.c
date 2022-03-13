/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:57:43 by ghanh             #+#    #+#             */
/*   Updated: 2022/03/11 21:06:07 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	check_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (CORR_CHAR);
	else if (c == '1' || c == '0' || c == ' ')
		return (CORR_SIGN);
	return (0);
}

static	int	help(char **map, int y, int x, int flag)
{
	if (!check_char(map[y][x]))
		return (1);
	else if (check_char(map[y][x]) == CORR_CHAR && flag)
		return (1);
	else if (((map[y][x] != ' ' && map[y][x] != '1') && ((y != 0 &&
			(map[y - 1][x]) && map[y - 1][x] == ' ')
			|| (map[y + 1] && ((ft_strlen(map[y + 1]) <= x)
			|| map[y + 1][x] == ' '))
			|| (map[y][x - 1] && map[y][x - 1] == ' ')
			|| (!map[y][x + 1] || map[y][x + 1] == ' '))))
		return (1);
	return (0);
}

void	check(int flag)
{
	if (!flag)
		error_msg("Not valid map\n");
}

void	check_my_map(char **map)
{
	t_iter	it;

	ft_memset(&it, 0, sizeof(t_iter));
	while (map[it.x])
		it.x++;
	it.height = it.x - 1;
	while (map[it.y])
	{
		it.x = 0;
		while (map[it.y][it.x])
		{
			if (((map[it.y][it.x] != ' ' && map[it.y][it.x] != '1') &&
			((it.y == 0
			|| it.y == it.height) || (it.x == 0 || it.x == ft_strlen(map[it
			.y]) - 1))))
				error_msg("Not valid map\n");
			else if (help(map, it.y, it.x, it.start))
				error_msg("Not valid map\n");
			if (check_char(map[it.y][it.x]) == CORR_CHAR)
				it.start = 1;
			it.x++;
		}
		it.y++;
	}
	check(it.start);
}
