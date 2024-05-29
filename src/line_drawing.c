/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:17:48 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/29 15:01:18 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/*
** line more vertical than horizontal
*/
static void	line_high(t_fdata *d, t_point *p0, t_point *p1, int deltas[2])
{
	int	xy[2];
	int	slope;
	int	err;
	int	inc[3]; //x,y,err

	xy[0] = p0->x;
	xy[1] = p0->y;
	slope = 2 * ft_abs(deltas[0]);
	err = -ft_abs(deltas[1]);
	inc[2] = -2 * ft_abs(deltas[1]);
	inc[0] = ft_sign(deltas[0]);
	inc[1] = ft_sign(deltas[1]);
	while (xy[1] != p1->y + inc[1])
	{
		put_pixel_img(&d->img, xy[0], xy[1], gradient(p0->color, p1->color,
				deltas[1], xy[1] - p0->y));
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
static void	line_low(t_fdata *d, t_point *p0, t_point *p1, int deltas[2])
{
	int	xy[2];
	int	slope;
	int	err;
	int	inc[3]; //x,y,err

	xy[0] = p0->x;
	xy[1] = p0->y;
	slope = 2 * ft_abs(deltas[1]);
	err = -ft_abs(deltas[0]);
	inc[2] = -2 * ft_abs(deltas[0]);
	inc[0] = ft_sign(deltas[0]);
	inc[1] = ft_sign(deltas[1]);
	while (xy[0] != p1->x + inc[0])
	{
		put_pixel_img(&d->img, xy[0], xy[1], gradient(p0->color, p1->color,
				deltas[0], xy[0] - p0->x));
		err += slope;
		if (err >= 0)
		{
			xy[1] += inc[1];
			err += inc[2];
		}
		xy[0] += inc[0];
	}
}

static void	line_straight(t_fdata *d, t_point *p0, t_point *p1, int deltas[2])
{
	int	xy[2];
	int	inc;

	xy[0] = p0->x;
	xy[1] = p0->y;
	if (deltas[1] == 0)
	{
		inc = ft_sign(deltas[0]);
		while (xy[0] != p1->x + inc)
		{
			put_pixel_img(&d->img, xy[0], xy[1], gradient(p0->color, p1->color,
					deltas[0], xy[0] - p0->x));
			xy[0] += inc;
		}
		return ;
	}
	inc = ft_sign(deltas[1]);
	while (xy[1] != p1->y + inc)
	{
		put_pixel_img(&d->img, xy[0], xy[1], gradient(p0->color, p1->color,
				deltas[1], xy[1] - p0->y));
		xy[1] += inc;
	}
}

static int	draw_line(t_fdata *d, t_point *p0, t_point *p1, int n)
{
	int	deltas[2];

	ft_printf("%d line\n", n);
	deltas[0] = p1->x - p0->x;
	deltas[1] = p1->y - p0->y;
	if (deltas[0] == 0 || deltas[1] == 0)
		line_straight(d, p0, p1, deltas);
	if (deltas[0] >= deltas[1])
		line_high(d, p0, p1, deltas);
	else
		line_low(d, p0, p1, deltas);
	return (1);
}

int	draw_lines(t_fdata *d)
{
	t_point	*pts;
	int		i;
	int n = 0;

	write(1, "draw_lines\n", 11);
	i = 0;
	pts = d->pts.arr;
	while (i < d->pts.size)
	{
		//Here i think to many lines are tried to draw
		if (i % d->pts.c != d->pts.c - 1
			&& (pts[i].visible || pts[i + 1].visible))
			draw_line(d, &pts[i], &pts[i + 1], ++n);
		if (i / d->pts.c != d->pts.r - 1
			&& (pts[i].visible || pts[i + d->pts.c].visible))
			draw_line(d, &pts[i], &pts[i + d->pts.c], ++n);
		i++;
	}
	write(1, "end draw_lines\n", 15);
	return (1);
}
