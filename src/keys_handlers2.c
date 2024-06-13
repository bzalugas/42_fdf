/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handlers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:58:36 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/13 18:37:59 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <math.h>

int	change_elevation(t_fdata *d, int key)
{
	if (key == KEY_J)
		d->img.elev += 0.5;
	else if (key == KEY_K)
		d->img.elev -= 0.5;
	rotate_img(d, AXIS_Y, true);
	rotate_img(d, AXIS_Z, false);
	rotate_img(d, AXIS_X, false);
	if (d->img.col_mode == COLOR_AUTO)
		auto_colors(d);
	d->img.refresh = true;
	return (1);
}

int	translate(t_fdata *d, int key)
{
	if (key == KEY_W || key == KEYM_W)
		d->img.ty -= 2;
	else if (key == KEY_S || key == KEYM_S)
		d->img.ty += 2;
	else if (key == KEY_A || key == KEYM_A)
		d->img.tx -= 2;
	else if (key == KEY_D || key == KEYM_D)
		d->img.tx += 2;
	rotate_img(d, AXIS_Y, true);
	rotate_img(d, AXIS_Z, false);
	rotate_img(d, AXIS_X, false);
	d->img.refresh = true;
	return (1);
}

int	reset(t_fdata *d)
{
	int	max;

	d->img.elev = 1.0;
	d->img.rx = DEFAULT_DEG_X;
	d->img.ry = 0;
	d->img.rz = DEFAULT_DEG_Z;
	d->img.tx = 0;
	d->img.ty = 0;
	max = ft_max(d->pts.r, d->pts.c);
	d->img.sp = ft_max((WIDTH / 2) / max, (HEIGHT / 2) / max);
	if (d->img.sp < DEFAULT_SPACE)
		d->img.sp = DEFAULT_SPACE;
	rotate_img(d, AXIS_Y, true);
	rotate_img(d, AXIS_Z, false);
	rotate_img(d, AXIS_X, false);
	d->img.tog_lines = 1;
	d->img.refresh = true;
	dynamic_hud(d);
	return (1);
}

int	toggle_lines(t_fdata *d)
{
	d->img.tog_lines = -d->img.tog_lines;
	d->img.refresh = true;
	return (1);
}
