/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:49:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/28 21:55:33 by bazaluga         ###   ########.fr       */
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

static void	create_image(t_fdata *d)
{
	d->img.ptr = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->img.ptr)
		stop_error("Error while creating image", d);
	d->img.addr = mlx_get_data_addr(d->img.ptr, &d->img.bpp, &d->img.size,
			&d->img.end);
}

int	put_points(t_fdata *d)
{
	int			i;
	t_point		*arr;
	int			color;

	if (!d->img.ptr)
		create_image(d);
	arr = d->pts.arr;
	i = 0;
	while (i < d->pts.size)
	{
		color = arr[i].color;
		arr[i].x = arr[i].i + arr[i].i * d->img.sp;
		arr[i].y = arr[i].j + arr[i].j * d->img.sp;
		arr[i].visible = true;
		if (arr[i].x < WIDTH && arr[i].y < HEIGHT)
			put_pixel_img(&d->img, arr[i].x, arr[i].y, color);
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
	//Optimization: instead of creating a black image then putting points,
	//fill all the image that doesn't have a point with black at each put_points
	if (d->img.ptr)
		ft_bzero(d->img.addr, d->img.size * HEIGHT);
	return (put_points(d));
}
