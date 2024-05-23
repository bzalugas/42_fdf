/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:49:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/23 15:48:36 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"

/*
** Convert 4 values of a color to an int
** Returns: the int representing the color
*/
int	trgb_to_i(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*
** Convert an int representing a color to 4 values (trgb)
** Set by reference r,g,b part of color
** Returns: transparency part of color
*/
int	i_to_trgb(int color, int *r, int *g, int *b)
{
	if (r)
		*r = (color >> 16) & 0xFF;
	if (g)
		*g = (color >> 8) & 0xFF;
	if (b)
		*b = color & 0xFF;
	return ((color >> 24) & 0xFF);
}

void	pixel_put_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (x * (img->bpp / 8) + y * img->size);
	*(unsigned int *)dst = color;
}

int	put_points(t_fdata *d)
{
	int			i;
	t_pts_arr	*pts;
	int			color;

	pts = &d->pts;
	if (!d->img.ptr)
	{
		d->img.ptr = mlx_new_image(d->mlx, pts->c * pts->c, pts->r * pts->r);
		if (!d->img.ptr)
			stop_error("Error while creating image", d);
		d->img.addr = mlx_get_data_addr(d->img.ptr, &d->img.bpp, &d->img.size,
						&d->img.end);
	}
	i = 0;
	while (pts->arr[i])
	{
		color = pts->arr[i]->color;
		pixel_put_img(&d->img, (i % pts->c) * 10, (i / pts->c) * 10, color);
		i++;
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img.ptr, 0, 0);
	return (1);
}
