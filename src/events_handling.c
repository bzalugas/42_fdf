/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:01:15 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/13 15:02:53 by bazaluga         ###   ########.fr       */
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

int	handle_key(int key, t_fdata *data)
{
	if (key == ESC || key == ESCM)
		return (handle_close(data));
	else if (key == KEY_I || key == KEYM_I)
		return (zoom_in(data));
	else if (key == KEY_O || key == KEYM_O)
		return (zoom_out(data));
	else if (key == KEY_Q || key == KEY_E || key == KEY_W || key == KEY_S
		|| key == KEY_A || key == KEY_D || key == KEYM_Q || key == KEYM_E
		|| key == KEYM_W || key == KEYM_S || key == KEYM_A || key == KEYM_D)
		return (rotate(data, key));
	else if (key == KEY_C)
		toggle_colors(data);
	else if (key == KEY_J || key == KEY_K)
		change_elevation(data, key);
	else
		return (get_keycode(key));
	return (1);
}
