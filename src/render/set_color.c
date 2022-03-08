#include "../../includes/cube3d.h"

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	void	*dst;

	dst = win->addr + (y * win->line_l + x * (win->bpp / 8));
	*(int*)dst = color;
}

int		get_texture_color(t_texture *texture, int x, int y)
{
	void	*dst;

	dst = texture->addr + (y * texture->line_length + x
													  * (texture->bits_per_pixel / 8));
	return (*(int*)dst);
}