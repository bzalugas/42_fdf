/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:59:30 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/16 19:12:47 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx.h"
#include "../include/fdf.h"
#include "../include/libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

void	pixel_put_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (x * (img->bpp / 8) + y * img->size_line);
	*(unsigned int *)dst = color;
}

int	close_frame(void *param)
{
	t_fdata	*frame;


	printf("HERE\n");
	frame = (t_fdata *)param;
	mlx_destroy_image(frame->mlx, frame->img.ptr);
	mlx_destroy_window(frame->mlx, frame->win);
	free(frame->mlx);
	ft_empty_trash(&frame->garbage);
	exit(0);
	return (0);
}

int	main(void)
{
	/* t_fdata	data; */
	/* int		i; */
	/* int		j; */
	char	*s;
	s = ft_strdup("coucou");
	ft_printf("%s", s);
	/* data.garbage = NULL; */
	/* s = ft_mylloc(sizeof(char) * 5, &data.garbage); */
	/* ft_strlcpy(s, "here\n", 5); */
	/* data.mlx = mlx_init(); */
	/* data.win = mlx_new_window(data.mlx, 1680, 900, "FDF"); */
	/* if (!data.win) */
	/* { */
	/* 	free(data.mlx); */
	/* 	return (1); */
	/* } */
	/* data.img.ptr = mlx_new_image(data.mlx, 500, 500); */
	/* data.img.addr = mlx_get_data_addr(data.img.ptr, &data.img.bpp, &data.img.size_line, &data.img.endian); */
	/* i = -1; */
	/* while (++i < 500) */
	/* { */
	/* 	j = -1; */
	/* 	while (++j < 500) */
	/* 		pixel_put_img(&data.img, i, j, 0x00F5F5F5); */
	/* } */
	/* mlx_put_image_to_window(data.mlx, data.win, data.img.ptr, 590, 225); */
	/* mlx_hook(data.win, 17, 0, &close_frame, &data); */
	/* mlx_loop(data.mlx); */
	/* close_frame(&data); */
	return (0);
}
