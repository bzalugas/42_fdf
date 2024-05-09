/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:59:30 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/08 12:41:52 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx.h"
#include "../include/fdf.h"
#include <stdlib.h>
#include <stdio.h>

void	pixel_put_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (x * (img->bits_per_pixel / 8) + y * img->size_line);
	*(unsigned int *)dst = color;
}

int	close(void *param)
{
	t_frame	*frame;

	printf("HERE\n");
	frame = (t_frame *)param;
	mlx_destroy_window(frame->mlx, frame->win);
	exit(0);
	/* return (0); */
}

int	main(void)
{
	t_frame	frame;
	t_img	img;
	int		i;
	int		j;

	frame.mlx = mlx_init();
	frame.win = mlx_new_window(frame.mlx, 1680, 900, "FDF");
	if (!frame.win)
	{
		free(frame.mlx);
		return (1);
	}
	img.ptr = mlx_new_image(frame.mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.size_line, &img.endian);
	i = -1;
	while (++i < 500)
	{
		j = -1;
		while (++j < 500)
			pixel_put_img(&img, i, j, 0x00F5F5F5);
	}
	mlx_put_image_to_window(frame.mlx, frame.win, img.ptr, 590, 225);
	mlx_hook(frame.win, 17, 0, &close, &frame);
	mlx_loop(frame.mlx);
	mlx_destroy_image(frame.mlx, img.addr);
	/* mlx_destroy_window(frame.mlx, frame.win); */
	return (0);
}
