#include "cube3d.h"

void	error_msg(char *str)
{
	ft_putstr_fd("Error\n", 2);
	if (errno == 0)
		ft_putstr_fd(str, 2);
	else
		perror(str);
	exit(EXIT_FAILURE);
}
