/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:59:30 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/22 13:04:53 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx.h"
#include "../include/fdf.h"
#include "../include/libft/libft.h"
#include <stdlib.h>

int	handle_esc(int keycode, t_fdata *data)
{
	if (keycode != ESC && keycode != ESCM)
		return (1);
	if (data->img.ptr)
		mlx_destroy_image(data->mlx, data->img.ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx2_destroy_display(data->mlx);
	ft_empty_trash(&data->trash);
	exit(0);
}

int	get_keycode(int keycode, void *param)
{
	(void)param;
	ft_printf("keycode = %d\n", keycode);
	return (0);
}

int	main(void)
{
	t_fdata	data;
	int		i;
	int		j;

	data = (t_fdata){0};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1680, 900, "Fil de Fer");
	if (!data.win)
	{
		free(data.mlx);
		return (1);
	}
	data.img.ptr = mlx_new_image(data.mlx, 500, 500);
	data.img.addr = mlx_get_data_addr(data.img.ptr, &data.img.bpp, &data.img.size_line, &data.img.endian);
	i = -1;
	while (++i < 500)
	{
		j = -1;
		while (++j < 500)
			pixel_put_img(&data.img, i, j, 0x00FF23F5);
	}
	mlx_put_image_to_window(data.mlx, data.win, data.img.ptr, 590, 225);
	mlx_hook(data.win, DESTROY, 0, &end_fdf, &data);
	mlx_hook(data.win, KEYDOWN, 1L<<0, &handle_esc, &data);
	mlx_loop(data.mlx);
	return (0);
}
