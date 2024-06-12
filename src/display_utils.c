/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:49:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/12 14:49:27 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"
#include "../include/libft.h"
#include <math.h>

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return ;
	dst = img->addr + (x * (img->bpp / 8) + y * img->size);
	*(unsigned int *)dst = color;
	/* ft_printf("wrote (%d,%d)\n", x, y); */
}

void	normalize_coords(t_fdata *d, t_point *origin)
{
	int		i;
	t_point	mid;

	if (!origin)
		mid = d->pts.arr[(d->pts.r / 2) * d->pts.c + (d->pts.c / 2)];
	else
		mid = *origin;
	i = -1;
	while (++i < d->pts.size)
	{
		d->pts.arr[i].i = d->pts.arr[i].i - mid.i;
		d->pts.arr[i].j = d->pts.arr[i].j - mid.j;
	}
}

void	create_image(t_fdata *d)
{
	d->img.ptr = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->img.ptr)
		stop_error("Error while creating image", d);
	d->img.addr = mlx_get_data_addr(d->img.ptr, &d->img.bpp, &d->img.size,
			&d->img.end);
}

void	config_img(t_fdata *d)
{
	d->img.offset[0] = DEFAULT_OFFSETX;
	d->img.offset[1] = DEFAULT_OFFSETY;
	d->img.center[0] = WIDTH / 2;
	d->img.center[1] = HEIGHT / 2;
	/* d->img.sp = ft_min(WIDTH / (d->pts.c + 1), HEIGHT / (d->pts.r + 1)); */
	if (d->img.sp < DEFAULT_SPACE)
		d->img.sp = DEFAULT_SPACE;
	d->img.ptslines = ft_cylloc(HEIGHT * WIDTH, sizeof(t_ptline), &d->trash);
	if (!d->img.ptslines)
		stop_error("ptslines allocation error", d);
	d->img.rx = DEFAULT_DEG_X;
	d->img.ry = 0;
	d->img.rz = DEFAULT_DEG_Z;
	rotate_img(d, AXIS_Z, true);
	rotate_img(d, AXIS_X, false);
	ft_printf("sp = %d\n", d->img.sp);
}
#include <stdio.h>
bool	is_infront(int xy[2], t_ptline *ptl, t_fdata *d, bool init)
{
	int			i;
	int			j;
	t_ptline	*actual;

	if (init)
	{
		i = 0;
		while (i < HEIGHT)
		{
			j = 0;
			while (j < WIDTH)
			{
				d->img.ptslines[WIDTH * i + j] = (t_ptline){.draw = false,
					.z0 = 0.0, .z1 = 0.0};
				j++;
			}
			i++;
		}
		return (true);
	}
	if (xy[0] >= WIDTH || xy[0] < 0 || xy[1] >= HEIGHT || xy[1] < 0)
		return (false);
	/* actual = &d->ptslines[xy[0]][xy[1]]; */
	actual = &d->img.ptslines[WIDTH * xy[1] + xy[0]];
	if (!actual->draw)
	{
		*actual = *ptl;
		return (true);
	}
	if (actual->draw && actual->z0 < ptl->z0 && actual->z1 < ptl->z1)
		//Problem when d->img.rx > 90 (lines of altitude appears infront)
	{
		printf("conflict: actual zs = %f->%f, news = %f->%f\n", actual->z0, actual->z1,
			ptl->z0, ptl->z1);
		*actual = *ptl;
		return (true);
	}
	return (false);
}
