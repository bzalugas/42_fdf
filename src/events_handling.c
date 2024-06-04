/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:01:15 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/04 19:55:48 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	handle_close(t_fdata *data)
{
	end_fdf(data, 0);
	exit(0);
}

static int	get_keycode(int keycode)
{
	ft_printf("keycode = %d\n", keycode);
	return (1);
}

static int	zoom_in(t_fdata *d)
{
	d->img.sp++;
	rotate_img(d, AXIS_Y, true);
	rotate_img(d, AXIS_Z, false);
	rotate_img(d, AXIS_X, false);
	d->img.refresh = true;
	return (1);
}

static int	zoom_out(t_fdata *d)
{
	if (d->img.sp - 1 > 0)
		d->img.sp--;
	rotate_img(d, AXIS_Y, true);
	rotate_img(d, AXIS_Z, false);
	rotate_img(d, AXIS_X, false);
	d->img.refresh = true;
	return (1);
}

static int	rotate(t_fdata *d, int key)
{
	if (key == KEY_Q)
		d->img.rz++;
	else if (key == KEY_E)
		d->img.rz--;
	else if (key == KEY_W)
		d->img.rx++;
	else if (key == KEY_S)
		d->img.rx--;
	else if (key == KEY_D)
		d->img.ry++;
	else if (key == KEY_A)
		d->img.ry--;
	rotate_img(d, AXIS_Y, true);
	rotate_img(d, AXIS_Z, false);
	rotate_img(d, AXIS_X, false);
	d->img.refresh = true;
	return (1);
}

int	handle_key(int key, t_fdata *data)
{
	if (key == ESC || key == ESCM)
		return (handle_close(data));
	else if (key == KEY_I || key == KEYM_I)
		return (zoom_in(data));
	else if (key == KEY_O || key == KEYM_O)
		return (zoom_out(data));
	else if (key == KEY_Q || key == KEY_E || key == KEY_W || key == KEY_S
		|| key == KEY_A || key == KEY_D)
		return (rotate(data, key));
	else
		return (get_keycode(key));
	return (1);
}
