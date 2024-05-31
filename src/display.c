/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:11:41 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/31 19:03:15 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"
#include <math.h>

void	get_coords(t_fdata *d, t_point *p)
{
	p->x = (WIDTH/2) + (p->i * d->img.sp);
	p->y = (HEIGHT/2) + (p->j * d->img.sp);
	/* p->z = p->h; */
	/* p->x = p->i + (p->i * d->img.sp); */
	/* p->y = p->j + (p->j * d->img.sp); */
}

void convert_3d_2d(t_point *p)
{
	int	x2;

	x2 = p->x - p->y;
	p->y = (p->x + p->y) / 2 - p->z;
	p->x = x2;
	ft_printf("final coords = (%d,%d,%d)\n", p->x, p->y, p->z);
}

static int	put_points(t_fdata *d, int zoom)
{
	int			i;
	t_point		*arr;

	if (!d->img.ptr)
		create_image(d);
	arr = d->pts.arr;
	i = 0;
	while (i < d->pts.size)
	{
		if (zoom > 0 && arr[i].z != 0)
			arr[i].z++;
		else if (zoom < 0 && arr[i].z != 0)
			arr[i].z--;
		/* arr[i].x = arr[i].i; */
		/* arr[i].y = arr[i].j; */
		/* arr[i].z = arr[i].h; */
		get_coords(d, &arr[i]);
		/* rotate_y(&arr[i], ANGLE_Y); */
		/* rotate_x(&arr[i], ANGLE_X); */
		convert_3d_2d(&arr[i]);
		arr[i].visible = true;
		if (arr[i].x < WIDTH && arr[i].x >= 0
			&& arr[i].y < HEIGHT && arr[i].y >= 0)
			put_pixel_img(&d->img, arr[i].x, arr[i].y, arr[i].color);
		else
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
	int	diff;
	//Optimization: instead of creating a black image then putting points,
	//fill all the image that doesn't have a point with black at each put_points
	if (!d->img.ptr)
		return (0);
	if (d->img.old_sp != d->img.sp)
	{
		diff = d->img.sp - d->img.old_sp;
		ft_bzero(d->img.addr, d->img.size * HEIGHT);
		d->img.old_sp = d->img.sp;
		return (put_points(d, diff));
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
	put_points(d, 0);
	mlx_loop_hook(d->mlx, &refresh_display, d);
	mlx_hook(d->win, DESTROY, 0, &handle_close, d);
	mlx_hook(d->win, KEYDOWN, 1L << 0, &handle_key, d);
	mlx_loop(d->mlx);
}
