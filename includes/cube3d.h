#ifndef CUBE3D_h
# define CUBE3D_h

# include "../42-libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


# define NOTSET -1
# define CORR_CHAR 1
# define CORR_SIGN 2
typedef struct s_color
{
    int R;
    int G;
    int B;
}t_color;

typedef struct s_map
{
    char    **my_map;
    char    *north;
    char    *south;
    char    *weast;
    char    *east;
    t_color floor;
    t_color ceil;
    
}t_map;

typedef struct s_iter
{
    int x;
    int y;
    int border;
    int start;
    int height;
}t_iter;

// error.c
void	error_msg(char *str);

//main (was in Slava's libft)
int	ft_strcmp(const char *s1, const char *s2);

//parser
int check_map(char *str, t_map *map);
#endif