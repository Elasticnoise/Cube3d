/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:43:46 by ghanh             #+#    #+#             */
/*   Updated: 2022/03/11 21:05:57 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	find_unit_help(t_player *plr, t_iter it, char **my_map)
{
	plr->x = it.border * SIZE + 32;
	plr->y = it.height * SIZE + 32;
	if (my_map[it.height][it.border] == 'N')
		plr->dir = 270;
	else if (my_map[it.height][it.border] == 'W')
		plr->dir = 180;
	else if (my_map[it.height][it.border] == 'E')
		plr->dir = 0;
	else
		plr->dir = 90;
}

void	find_unit(t_player	*plr, char **my_map)
{
	t_iter	it;

	it.y = 0;
	while (my_map[it.y])
	{
		it.x = 0;
		while (my_map[it.y][it.x])
		{
			if (check_char(my_map[it.y][it.x]) == CORR_CHAR)
			{
				it.height = it.y;
				it.border = it.x;
			}
			it.x++;
		}
		it.y++;
	}
	find_unit_help(plr, it, my_map);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static int	check_lenght(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0' && str[i])
		i++;
	if (i > 10)
		return (1);
	return (0);
}

int	cust_atoi(char *str)
{
	long long int	answ;

	answ = 0;
	if (*str != '+' && (*str < '0' || *str > '9') && (*str != ' '))
		error_msg("Not valid map\n");
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (!(*str >= '0' && *str <= '9') || check_lenght(str))
		error_msg("Not valid map\n");
	while (*str >= '0' && *str <= '9')
	{
		answ = answ * 10 + (*str - '0');
		str++;
	}
	while ((*str) == ' ')
		str++;
	if ((*str != ' ' && *str != '\0') || (answ > 255 || answ < 0))
		error_msg("Not valid map\n");
	return (answ);
}
