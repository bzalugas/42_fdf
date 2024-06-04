/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:11:41 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/04 19:30:18 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"
#include <math.h>

void	get_coords(t_fdata *d, t_point *p)
{
	p->x = round(d->img.center[0] + p->x);
	p->y = round(d->img.center[1] + p->y);
}

#include <stdio.h>
static int	put_points(t_fdata *d)
{
	int			i;
	t_point		*arr;

	if (!d->img.ptr)
		create_image(d);
	arr = d->pts.arr;
	i = 0;
	while (i < d->pts.size)
	{
		/* arr[i].x = arr[i].i * d->img.sp; */
		/* arr[i].y = arr[i].j * d->img.sp; */
		/* arr[i].z = arr[i].k * 5; //kinda stupid ofc */
		/* rotate_z(&arr[i], d->img.rz); */
		/* rotate_x(&arr[i], d->img.rx); */
		/* rotate_y(&arr[i], d->img.ry); */
		get_coords(d, &arr[i]);
		arr[i].visible = true;
		/* if (arr[i].x < WIDTH && arr[i].x >= 0 */
		/* 	&& arr[i].y < HEIGHT && arr[i].y >= 0) */
		/* 	put_pixel_img(&d->img, arr[i].x, arr[i].y, arr[i].color); */
		/* else */
		/* 	arr[i].visible = false; */
		if (arr[i].x >= WIDTH || arr[i].x < 0
			|| arr[i].y >= HEIGHT || arr[i].y < 0)
			arr[i].visible = false;
		i++;
	}
	draw_lines(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img.ptr, d->img.offset,
		d->img.offset);
	return (1);
}

int	refresh_display(t_fdata *d)
{
	/* int	diff; */
	//Optimization: instead of creating a black image then putting points,
	//fill all the image that doesn't have a point with black at each put_points
	if (!d->img.ptr)
		return (0);
	if (d->img.refresh)
	{
		d->img.refresh = false;
		/* diff = d->img.sp - d->img.old_sp; */
		ft_bzero(d->img.addr, d->img.size * HEIGHT);
		return (put_points(d));
	}
	return (1);
}

void	test_lines(t_fdata *d);

void	display(t_fdata *d)
{
	d->mlx = mlx_init();
	if (!d->mlx)
		stop_error("Error at mlx initialization", d);
	config_img(d);
	d->win = mlx_new_window(d->mlx, WIDTH + d->img.offset,
			HEIGHT + d->img.offset, "FdF");
	if (!d->win)
		stop_error("Error at mlx window initialization", d);
	/* test_lines(d); */
	put_points(d);
	mlx_loop_hook(d->mlx, &refresh_display, d);
	mlx_hook(d->win, DESTROY, 0, &handle_close, d);
	mlx_hook(d->win, KEYDOWN, 1L << 0, &handle_key, d);
	mlx_loop(d->mlx);
}
