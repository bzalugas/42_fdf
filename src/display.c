/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:11:41 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/14 15:12:03 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"
#include <math.h>

static void	get_coords(t_fdata *d, t_point *p)
{
	if (!d->img.normalized)
	{
		p->x = round(d->img.center[0] + p->x + d->img.tx);
		p->y = round(d->img.center[1] + p->y + d->img.ty);
	}
}

static int	put_points(t_fdata *d)
{
	size_t		i;
	t_point		*arr;

	if (!d->img.ptr)
		create_image(d);
	arr = d->pts.arr;
	i = 0;
	init_pixels_arr(d);
	while (i < d->pts.size)
	{
		get_coords(d, &arr[i]);
		arr[i].visible = true;
		if (arr[i].x >= WIDTH || arr[i].x < 0
			|| arr[i].y >= HEIGHT || arr[i].y < 0)
			arr[i].visible = false;
		else if (d->img.tog_lines == -1 && pt_infront(&arr[i], d))
			put_pixel_img(&d->img, arr[i].x, arr[i].y, arr[i].color);
		i++;
	}
	d->img.normalized = true;
	if (d->img.tog_lines == 1)
		draw_lines(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img.ptr, d->img.offset[0],
		d->img.offset[1]);
	return (1);
}

int	refresh_display(t_fdata *d)
{
	if (!d->img.ptr)
		return (0);
	if (d->img.refresh)
	{
		d->img.refresh = false;
		ft_bzero(d->img.addr, d->img.size * HEIGHT);
		return (put_points(d));
	}
	return (1);
}

void	display(t_fdata *d, char *filename)
{
	char	*title;

	d->mlx = mlx_init();
	if (!d->mlx)
		stop_error("Error at mlx initialization", d);
	config_img(d);
	title = ft_strjoin("FdF:  ", filename);
	d->win = mlx_new_window(d->mlx, WIDTH + d->img.offset[0],
			HEIGHT + d->img.offset[1], title);
	free(title);
	if (!d->win)
		stop_error("Error at mlx window initialization", d);
	display_hud(d);
	put_points(d);
	mlx_loop_hook(d->mlx, &refresh_display, d);
	mlx_hook(d->win, DESTROY, 0, &handle_close, d);
	mlx_hook(d->win, KEYDOWN, 1L << 0, &handle_key, d);
	mlx_hook(d->win, MOUSEDOWN, 1L << 2, &handle_mouse, d);
	mlx_loop(d->mlx);
}
