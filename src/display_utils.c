/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:49:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/26 22:36:04 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"
#include "../include/libft/libft.h"

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

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return ;
	dst = img->addr + (x * (img->bpp / 8) + y * img->size);
	*(unsigned int *)dst = color;
}

/*
** line more vertical than horizontal
*/
static void line_high(t_fdata *d, t_point *p0, t_point *p1)
{
	int	xy[2];
	int	deltas[2]; //dx, dy
	int	slope;
	int	err;
	int	inc[3]; //x,y,err

	xy[0] = p0->x;
	xy[1] = p0->y;
	deltas[0] = p1->x - p0->x;
	deltas[1] = p1->y - p0->y;
	slope = 2 * ft_abs(deltas[0]);
	err = -ft_abs(deltas[1]);
	inc[2] = -2 * ft_abs(deltas[1]);
	inc[0] = ft_sign(deltas[0]);
	inc[1] = ft_sign(deltas[1]);
	while (xy[1] != p1->y + inc[1])
	{
		put_pixel_img(&d->img, xy[0], xy[1], p0->color);//do a gradient
		err += slope;
		if (err >= 0)
		{
			xy[0] += inc[0];
			err += inc[2];
		}
		xy[1] += inc[1];
	}
}

/*
** Line more horizontal than vertical
*/
static void line_low(t_fdata *d, t_point *p0, t_point *p1)
{
	int	xy[2];
	int	deltas[2]; //dx, dy
	int	slope;
	int	err;
	int	inc[3]; //x,y,err

	xy[0] = p0->x;
	xy[1] = p0->y;
	deltas[0] = p1->x - p0->x;
	deltas[1] = p1->y - p0->y;
	slope = 2 * ft_abs(deltas[1]);
	err = -ft_abs(deltas[0]);
	inc[2] = -2 * ft_abs(deltas[0]);
	inc[0] = ft_sign(deltas[0]);
	inc[1] = ft_sign(deltas[1]);
	while (xy[0] != p1->x + inc[0])
	{
		put_pixel_img(&d->img, xy[0], xy[1], p0->color);//do a gradient
		err += slope;
		if (err >= 0)
		{
			xy[1] += inc[1];
			err += inc[2];
		}
		xy[0] += inc[0];
	}
}

static void	line_horizontal(t_fdata *d, t_point *p0, t_point *p1)
{
	int	xy[2];
	int	dx;
	int	incx;

	dx = p1->x - p0->x;
	xy[0] = p0->x;
	xy[1] = p0->y;
	incx = ft_sign(dx);
	while (xy[0] != p1->x + incx)
	{
		put_pixel_img(&d->img, xy[0], xy[1], p0->color);
		xy[0] += incx;
	}
}

static void	line_vertical(t_fdata *d, t_point *p0, t_point *p1)
{
	int	xy[2];
	int	dy;
	int	incy;

	dy = p1->y - p0->y;
	xy[0] = p0->x;
	xy[1] = p0->y;
	incy = ft_sign(dy);
	while (xy[1] != p1->y + incy)
	{
		put_pixel_img(&d->img, xy[0], xy[1], p0->color);
		xy[1] += incy;
	}
}

int	draw_line(t_fdata *d, t_point *p0, t_point *p1)
{
	int	dx;
	int	dy;

	dx = p1->x - p0->x;
	dy = p1->y - p0->y;
	if (dx == 0)
		line_vertical(d, p0, p1);
	else if (dy == 0)
		line_horizontal(d, p0, p1);
	else if (dx >= dy)
		line_high(d, p0, p1);
	else
		line_low(d, p0, p1);
	return (1);
}

int	draw_lines(t_fdata *d)
{
	t_point	*pts;
	int		i;

	i = 0;
	pts = d->pts.arr;
	while (i < d->pts.size)
	{
		if (i % d->pts.c != d->pts.c - 1
			&& (pts[i].visible || pts[i + 1].visible))
			draw_line(d, &pts[i], &pts[i + 1]);
		if (i / d->pts.c != d->pts.r - 1
			&& (pts[i].visible || pts[i + d->pts.c].visible))
			draw_line(d, &pts[i], &pts[i + d->pts.c]);
		i++;
	}
	return (1);
}
//Mix put_points & draw_lines to read array only one time
int	put_points(t_fdata *d)
{
	int			i;
	t_pts_arr	*pts;
	int			color;
	int			x;
	int			y;

	if (!d->img.ptr)
	{
		d->img.ptr = mlx_new_image(d->mlx, WIDTH, HEIGHT);
		if (!d->img.ptr)
			stop_error("Error while creating image", d);
		d->img.addr = mlx_get_data_addr(d->img.ptr, &d->img.bpp, &d->img.size,
				&d->img.end);
	}
	pts = &d->pts;
	i = 0;
	while (i < pts->size)
	{
		color = pts->arr[i].color;
		x = pts->arr[i].i + pts->arr[i].i * (d->img.spx * d->img.scale); //change with x
		y = pts->arr[i].j + pts->arr[i].j * (d->img.spy * d->img.scale); //change with y
		pts->arr[i].visible = true;
		if (x < WIDTH && y < HEIGHT)
			put_pixel_img(&d->img, x, y, color);
		else
			pts->arr[i].visible = false;
		pts->arr[i].x = x;
		pts->arr[i].y = y;
		i++;
	}
	draw_lines(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img.ptr, d->img.offset, d->img.offset);
	return (1);
}

int	refresh_display(t_fdata *d)
{
	if (d->img.ptr)
	{
		ft_bzero(d->img.addr, d->img.size * HEIGHT);
		mlx_put_image_to_window(d->mlx, d->win, d->img.ptr, d->img.offset, d->img.offset);
	}
	return (put_points(d));
}
