/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:52:35 by ghanh             #+#    #+#             */
/*   Updated: 2022/03/10 21:52:36 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_map(char *str, t_map *map)
{
	char	*help_str;
	int		fd;
	char	**map_str;

	ft_memset(map, 0, sizeof(t_map));
	map->floor.R = NOTSET;
	map->ceil.R = NOTSET;
	help_str = ft_strrchr(str, '.');
	if (!help_str || ft_strcmp(help_str, ".cub"))
		error_msg("Not correct format of the file\n");
	fd = open(str, O_RDONLY);
	if (fd == -1)
		error_msg("Error");
	map_str = parsing(fd, str);
	if (!map_str)
		error_msg("Malloc failed\n");
	set_map(map, map_str);
	free_map(map_str);
	check_my_map(map->my_map);
	map->width = ft_strlen(map->my_map[0]);
	while (map->my_map[map->height])
		map->height++;
	return (0);
}

char	**parsing(int file, char *file_name)
{
	int		rd;
	int		buf[8];
	int		size;
	char	*str;
	char	**str_split;

	size = 0;
	rd = 1;
	while (rd > 0)
	{
		rd = read(file, buf, 8);
		size += rd;
	}
	str = ft_calloc(size + 1, 1);
	close(file);
	file = open(file_name, O_RDONLY);
	rd = read(file, str, size);
	if (rd != size)
		error_msg("Read error");
	close(rd);
	str_split = ft_split(str, '\n');
	if (!str_split)
		error_msg("Malloc error\n");
	free(str);
	return (str_split);
}

void	set_rgb(char *str, t_color *color)
{
	int		i;
	char	**help;

	if (color->R != NOTSET)
		error_msg("Not valid map\n");
	i = 2;
	while (str[i] == ' ')
		i++;
	help = ft_split(str + i, ',');
	if (!help)
		error_msg("Malloc failed\n");
	i = 0;
	while (help[i])
		i++;
	if (i != 3)
		error_msg("Not valid map\n");
	color->R = cust_atoi(help[0]);
	color->G = cust_atoi(help[1]);
	color->B = cust_atoi(help[2]);
	i = 2;
	while (i > -1)
		free(help[i--]);
	free(help);
}

void	set_path(char *str, char **new)
{
	int	i;

	if (*new)
		error_msg("Not valid map\n");
	i = 2;
	while (str[i] == ' ')
		i++;
	*new = ft_substr(str, i, ft_strlen(str) - i);
	if (!(*new))
		error_msg("Malloc failed\n");
}
