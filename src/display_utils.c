/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:49:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/31 16:04:29 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"
#include "../include/libft/libft.h"
#include <math.h>

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return ;
	dst = img->addr + (x * (img->bpp / 8) + y * img->size);
	*(unsigned int *)dst = color;
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
	d->img.offset = DEFAULT_OFFSET;
	d->img.sp = 10;
	/* d->img.sp = ft_min((WIDTH - d->img.offset) / (d->pts.c + 1), */
	/* 		(HEIGHT - d->img.offset) / (d->pts.r + 1)); */
	/* if (d->img.sp < DEFAULT_SPACE) */
	/* 	d->img.sp = DEFAULT_SPACE; */
	d->img.old_sp = d->img.sp;
	ft_printf("sp = %d\n", d->img.sp);
}
