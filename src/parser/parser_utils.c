/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:43:46 by ghanh             #+#    #+#             */
/*   Updated: 2022/03/10 21:43:48 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
				plr->x = (float) it.x * SIZE + 32;
				plr->y = (float) it.x * SIZE + 32;
			}
			it.x++;
		}
		it.y++;
	}
	if (my_map[(int)plr->y / SIZE][(int)plr->x / SIZE] == 'N')
		plr->dir = 3 * M_PI_2;
	else if (my_map[(int)plr->y / SIZE][(int)plr->x / SIZE] == 'W')
		plr->dir = 2 * M_PI_2;
	else if (my_map[(int)plr->y / SIZE][(int)plr->x / SIZE] == 'E')
		plr->dir = 0;
	else
		plr->dir = M_PI_2;
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
		error_msg("Not Valid map\n");
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (!(*str >= '0' && *str <= '9') || check_lenght(str))
		error_msg("Not Valid map\n");
	while (*str >= '0' && *str <= '9')
	{
		answ = answ * 10 + (*str - '0');
		str++;
	}
	while ((*str) == ' ')
		str++;
	if ((*str != ' ' && *str != '\0') || (answ > 255 || answ < 0))
		error_msg("Not Valid map\n");
	return (answ);
}
