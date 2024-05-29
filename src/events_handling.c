/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:01:15 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/29 10:54:30 by bazaluga         ###   ########.fr       */
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
	/* refresh_display(d); */
	return (1);
}

static int	zoom_out(t_fdata *d)
{
	if (d->img.sp - 1 >= 0)
		d->img.sp--;
	/* refresh_display(d); */
	return (1);
}

int	handle_key(int keycode, t_fdata *data)
{
	if (keycode == ESC || keycode == ESCM)
		return (handle_close(data));
	else if (keycode == KEY_I || keycode == KEYM_I)
		return (zoom_in(data));
	else if (keycode == KEY_O || keycode == KEYM_O)
		return (zoom_out(data));
	else
		return (get_keycode(keycode));
	return (1);
}
