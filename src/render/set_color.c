/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:06:50 by lechalme          #+#    #+#             */
/*   Updated: 2022/03/11 21:06:51 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	void	*dst;

	dst = win->addr + (y * win->line_l + x * (win->bpp / 8));
	*(int *)dst = color;
}

int	get_texture_color(t_texture *texture, int x, int y)
{
	void	*dst;

	dst = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	return (*(int *)dst);
}

int	rgb_to_int(unsigned char r, unsigned char g, unsigned char b)
{
	return ((r << 16) | (g << 8) | b);
}
