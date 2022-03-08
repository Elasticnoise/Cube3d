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

# define W 13
# define A 0
# define S 1
# define D 2
# define TXTR_H 64
# define TXTR_W 64
# define WIN_X 1024
# define WIN_Y 768
# define SIZE 16
# define NOTSET -1
# define CORR_CHAR 1
# define CORR_SIGN 2
# define	GC 0x990099

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
    char    *west;
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
	char	*addr;
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
	int			z_buffer[1024];
	double		perp_wall_dist;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		plane_x;
	double		plane_y;
	int			hit;
	double		step;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	int			side;
	int			**map;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		txtr_pos;
	int			txtr_x;
	int			txtr_y;
	int			txtr_num;
	double		wall_x;
	int			color;
	double		rot_speed;
	double		move_speed;
}				  t_plr;

typedef struct	s_img
{
	void				*img;
	int					*addr;
	int					bits_per_pixel;
	int					size_l;
	int					line_length;
	int					endian;
	int					img_width;
	int					img_height;
}				t_img;

typedef struct s_all
{
	short	key[512];
	int		buff[WIN_Y][WIN_X];
	long	curr_time;
	int		*textures[6];
	short	key_l;
	short	key_r;
	t_win	*win;
	t_map	*map;
	t_plr	*plr;
	t_img	*mlx_image;
}t_all;

// error.c
void	error_msg(char *str);
int		create_trgb(int r, int g, int b);
int	ft_strcmp(const char *s1, const char *s2);
void	floor_ceiling(t_all *all);
void	rotate_screen_to_right(t_all *all);
void	rotate_screen_to_left(t_all *all);
void	move_straight(t_all *all);
void	move_back(t_all *all);
void	move_to_right(t_all *all);
void	key_update(t_all *all);
void	move_to_left(t_all *all);
void	key_update(t_all *all);

//parser
int 	check_map(char *str, t_map *map);
int 	check_char(char c);
void	find_unit(t_plr	*plr, char **my_map);
void	draw(t_all *all);
void	actions(int keycode, int x, int y, t_all *all);
void	*free_array(char **arr);
void	scale(t_win *win, int color, int x1, int y1);
void draw_player(t_all *all, t_plr *pl);
#endif