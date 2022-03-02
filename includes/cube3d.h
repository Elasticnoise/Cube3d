#ifndef CUBE3D_h
# define CUBE3D_h

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
# include "../mlx/mlx.h"
#include <math.h>

# define SIZE 16
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

typedef struct s_win
{
	void	*mlx;
	void	*img;
	void	*mlx_win;
	void	*addr;
	int		line_l;
	int		bpp;
	int		en;

}t_win;

typedef struct	s_plr //структура для игрока и луча
{
	float		x;
	float		y;
	float		dir;
	float		start;
	float		end;
}				  t_plr;

typedef struct s_all
{
	t_win	*win;
	t_map	*map;
	t_plr	plr;
}t_all;

// error.c
void	error_msg(char *str);

//main (was in Slava's libft)
int	ft_strcmp(const char *s1, const char *s2);

//parser
int check_map(char *str, t_map *map);
#endif