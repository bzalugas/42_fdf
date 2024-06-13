/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:38:12 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:31 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	zoom_in(t_fdata *d)
{
	d->img.sp++;
	rotate_img(d, AXIS_Y, true);
	rotate_img(d, AXIS_Z, false);
	rotate_img(d, AXIS_X, false);
	d->img.refresh = true;
	return (1);
}

int	zoom_out(t_fdata *d)
{
	if (d->img.sp - 1 > 0)
		d->img.sp--;
	rotate_img(d, AXIS_Y, true);
	rotate_img(d, AXIS_Z, false);
	rotate_img(d, AXIS_X, false);
	d->img.refresh = true;
	return (1);
}

static int	normalize_angles(t_fdata *d)
{
	if ((int)d->img.rz >= 360)
		d->img.rz -= 360;
	else if ((int)d->img.rz < 0)
		d->img.rz += 360;
	if ((int)d->img.rx >= 360)
		d->img.rx -= 360;
	else if ((int)d->img.rx < 0)
		d->img.rx += 360;
	if ((int)d->img.ry >= 360)
		d->img.ry -= 360;
	else if ((int)d->img.ry < 0)
		d->img.ry += 360;
	return (1);
}

int	rotate(t_fdata *d, int key)
{
	if (key == KEY_E || key == KEYM_E)
		d->img.rz++;
	else if (key == KEY_Q || key == KEYM_Q)
		d->img.rz--;
	else if (key == KEY_W || key == KEYM_W)
		d->img.rx++;
	else if (key == KEY_S || key == KEYM_S)
		d->img.rx--;
	else if (key == KEY_D || key == KEYM_D)
		d->img.ry++;
	else if (key == KEY_A || key == KEYM_A)
		d->img.ry--;
	normalize_angles(d);
	rotate_img(d, AXIS_Y, true);
	rotate_img(d, AXIS_Z, false);
	rotate_img(d, AXIS_X, false);
	d->img.refresh = true;
	dynamic_hud(d);
	return (1);
}

int	toggle_colors(t_fdata *d)
{
	if (d->img.col_mode == COLOR_RAW)
		d->img.col_mode = COLOR_AUTO;
	else
		d->img.col_mode = COLOR_RAW;
	if (d->img.col_mode == COLOR_RAW)
		reset_colors(d);
	else
		auto_colors(d);
	d->img.refresh = true;
	dynamic_hud(d);
	return (1);
}
