#include "../../includes/cube3d.h"


void	find_unit(t_plr	*plr, char **my_map)
{
	int		i;
	int		j;

	i = 0;
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
	if (my_map[(int)plr->y / SIZE][(int)plr->x / SIZE] == 'N')
		plr->dir = 3 * M_PI_2;
	else if (my_map[(int)plr->y / SIZE][(int)plr->x / SIZE] == 'W')
		plr->dir = 2 * M_PI_2;
	else if (my_map[(int)plr->y / SIZE][(int)plr->x / SIZE] == 'E')
		plr->dir = 0;
	else
		plr->dir = M_PI_2;
}

void    free_map(char **map)
{
    int i;

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

static int	cust_atoi(char *str)
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

void    set_rgb(char *str, t_color *color)
{
    int     i;
    char    **help;

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

void    set_path(char *str, char **new)
{
    int i;

    if (*new)
        error_msg("Not valid map\n");
    i = 2;
    while (str[i] == ' ')
        i++;
    *new = ft_substr(str, i, ft_strlen(str) - i);
    if (!(*new))
        error_msg("Malloc failed\n");
}

void    map_to_char(int i, char **old_map, char **new_map[])
{
	t_iter	iter;
	char	*help;

	ft_memset(&iter, 0, sizeof(t_iter));
	while (old_map[i][0] == '\n')
		i++;
	iter.start = i;
	while (old_map[i])
	{
		if (ft_strlen(old_map[i]) > iter.border)
			iter.border = ft_strlen(old_map[i]);
		i++;
	}
	(*new_map) = ft_calloc(sizeof(char *), i - iter.start + 1);
	help = ft_calloc(sizeof(char), iter.border + 1);
	if (!(*new_map) || !help)
		error_msg("Malloc failed\n");
	help = ft_memset(help, ' ', iter.border);
	while (old_map[iter.start])
	{
		(*new_map)[iter.y] = ft_substr(help, 0, iter.border);
		if (!(*new_map)[iter.y])
			error_msg("Malloc failed");
		(*new_map)[iter.y] = ft_memcpy((*new_map)[iter.y], old_map[iter
		.start], ft_strlen(old_map[iter.start]));
		iter.y++;
		iter.start++;
	}
	free(help);
}

void    set_map(t_map *map, char **map_str)
{
    int i;

    i = 0;
    while (map_str[i])
    {
        if (!ft_strncmp(map_str[i], "NO ", 3))
            set_path(map_str[i], &(map->north));
        else if (!ft_strncmp(map_str[i], "SO ", 3))
            set_path(map_str[i], &(map->south));
        else if (!ft_strncmp(map_str[i], "WE ", 3))
            set_path(map_str[i], &(map->west));
        else if (!ft_strncmp(map_str[i], "EA ", 3))
            set_path(map_str[i], &(map->east));
        else if (!ft_strncmp(map_str[i], "F ", 2))
            set_rgb(map_str[i], &(map->floor));
        else if (!ft_strncmp(map_str[i], "C ", 2))
            set_rgb(map_str[i], &(map->ceil));
        else if ((!(map->north) || !(map->south) || !(map->east) || !(map->west)
                || map->floor.R == NOTSET || map->ceil.R == NOTSET) && map_str[i][0] != '\n')
                error_msg("Not valid map\n");
        else
            {
                map_to_char(i, map_str, &map->my_map);
                return ;
            }
        i++;
    }
}

int check_char(char c)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return (CORR_CHAR);
    else if (c == '1' || c == '0' || c == ' ')
        return (CORR_SIGN);    
    return (0);   
}

void    check_my_map(char **map)
{
    t_iter it;

    ft_memset(&it, 0, sizeof(t_iter));
    while(map[it.x])
        it.x++;
    it.height = it.x;
    while (map[it.y])
    {
        it.x = 0;
        while (map[it.y][it.x])
        {
            if (!check_char(map[it.y][it.x])
             || (check_char(map[it.y][it.x]) == CORR_CHAR && it.start)
             || ((map[it.y][it.x] != ' ' && map[it.y][it.x] != '1') && ((it.y == 0 || it.y == it.height)
               || (it.x == 0 || it.x == ft_strlen(map[it.y]) - 1)))
             || ((map[it.y][it.x] != ' ' && map[it.y][it.x] != '1') && (
                 (it.y != 0 && (map[it.y - 1][it.x]) &&  map[it.y - 1][it.x] == ' ')
               || (map[it.y + 1] && ((ft_strlen(map[it.y + 1]) <= it.x) || map[it.y + 1][it.x] == ' '))
                || (map[it.y][it.x -1] && map[it.y][it.x - 1] == ' ')
                || (!map[it.y][it.x + 1]  || map[it.y][it.x + 1] == ' '))
                ))
                    error_msg("Not valid map\n");
            if (check_char(map[it.y][it.x]) == CORR_CHAR)
                it.start = 1;
            it.x++;
        }
        it.y++;
    }
}

int check_map(char *str, t_map *map)
{
	char    *help_str;
	int     fd;
	char    **map_str;

	ft_memset(map, 0, sizeof(t_map));
	map->floor.R = NOTSET;
	map->ceil.R = NOTSET;
	help_str = ft_strrchr(str, '.');
	if (!help_str || ft_strcmp(help_str, ".cub")) //todo check ".cub" case
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
