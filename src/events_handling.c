/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:01:15 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/26 22:37:30 by bazaluga         ###   ########.fr       */
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
	d->img.scale += 0.5;

	return (1);
}

static int	zoom_out(t_fdata *d)
{
	int	spx;
	int	spy;

	d->img.scale -= 0.5;
	spx = d->img.spx * d->img.scale;
	spy = d->img.spy * d->img.scale;
	if (spx < 0 || spy < 0)
		d->img.scale += 0.5;
	return (1);
}

int	handle_key(int keycode, t_fdata *data)
{
	if (keycode == ESC || keycode == ESCM)
		return (handle_close(data));
	else if (keycode == KEYM_I)
		return (zoom_in(data));
	else if (keycode == KEYM_O)
		return (zoom_out(data));
	else
		return (get_keycode(keycode));
	return (1);
}
