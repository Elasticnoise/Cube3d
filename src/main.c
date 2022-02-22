#include "cube3d.h"

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

int main(int argc, char *argv[])
{
    t_map map;

    if (argc != 2)
        error_msg("Not correct number of arguments\n");
    check_map(argv[1], &map);
    return (0);
}