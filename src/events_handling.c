/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:01:15 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/22 13:57:45 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"

int	handle_close(t_fdata *data)
{
	if (data->img.ptr)
		mlx_destroy_image(data->mlx, data->img.ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx2_destroy_display(data->mlx);
	ft_empty_trash(&data->trash);
	exit(0);
}

static int	handle_esc(t_fdata *data)
{
	end_fdf(data, 0);
	exit(0);
}


int	handle_key(int keycode, t_fdata *data)
{
	if (keycode == ESC || keycode == ESCM)
		return (handle_esc(data));
	return (0);
}
