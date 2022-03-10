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

#define WIN_WIDTH 620
#define WIN_HEIGHT 480
# define SIZE 64
# define NOTSET -1
# define CORR_CHAR 1
# define CORR_SIGN 2
#define	GC 0x990099
# define SOUTH 0
# define NORTH 1
# define WEST 2
# define EAST 3
# define ONE_RAY_ANGLE(fov, width) fov * 1.0 / width
# define NUM_OF_TEXT 4

typedef struct				s_line
{
	int						bot;
	int						top;
	int						x_pos;
	double					column_height;
}							t_line;

typedef struct s_color
{
    int R;
    int G;
    int B;
}t_color;

typedef struct				s_texture
{
	void					*img;
	int						text_x;
	int						text_y;
	char					*addr;
	int						width;
	int						height;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
}							t_texture;

typedef struct s_map
{
    char    	**my_map;
	t_texture	*texture;
    char    *north;
    char    *south;
    char    *west;
    char    *east;
    t_color floor;
    t_color ceil;
	int		height;
	int 	width; ////todo maybe need to fix
	int		bits_per_pixel;
	int		line_length;
	int		endian;

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
	char	*addr;
	int		line_l;
	int		bpp;
	int		en;

}t_win;

typedef struct				s_player {
	int						x;
	int						y;
	float					dir;
}							t_player;

typedef struct	s_plr //структура для игрока и луча
{
	float		x;
	float		y;
	float		dir;
	float		start;
	float		end;
	float		delta_x;
	float		delta_y;
	int			map_x;
	int			map_y;
	int			wall;
	float		wall_x;
	float		length;
	float		perp_length;
}				  t_plr;

typedef struct s_all
{
	t_win		*win;
	t_map		*map;
	t_plr		*plr;
	t_player	*player;
	int 		floor_color;
	int			ceil_color;
}t_all;

// error.c
void	error_msg(char *str);

//main (was in Slava's libft)
int	ft_strcmp(const char *s1, const char *s2);
float	vertical_tracing(t_all *game, double deg, t_plr *ray);
float	horizontal_tracing(t_all *game, double deg, t_plr *ray);
int		is_looking_up(float deg);
float	normalize_deg(float deg);
int		is_looking_right(float deg);
double	degrees_to_rad(double degrees);
float	intersection_detector(t_all *all, t_plr *ray, float distance);
void	north_or_south_wall(t_plr *result, t_plr ray, float dist, float deg);
void	west_or_east_wall(t_plr *result, t_plr ray, float dist, float deg);
void	draw_line(t_all *all, t_plr ray, t_line line);
void	draw_texture(t_all *all, t_plr ray, t_line line);
void	my_mlx_pixel_put(t_win *win, int x, int y, int color);
int		raycaster(t_all *all);
float	get_vector_length(t_all *game, t_plr ray);
int		get_texture_color(t_texture *texture, int x, int y);
//parser
int 	check_map(char *str, t_map *map);
int 	check_char(char c);
void	find_unit(t_player	*plr, char **my_map);
void	draw(t_all *all);
void	actions(int keycode, int x, int y, t_all *all);
void	*free_array(char **arr);
void	scale(t_win *win, int color, int x1, int y1);
void draw_player(t_all *all, t_plr *pl);
void    free_map(char **map);
#endif