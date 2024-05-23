/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:01:15 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/23 15:57:12 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"

int	handle_close(t_fdata *data)
{
	end_fdf(data, 0);
	exit(0);
}

int	get_keycode(int keycode)
{
	ft_printf("keycode = %d\n", keycode);
	return (0);
}

int	handle_key(int keycode, t_fdata *data)
{
	if (keycode == ESC || keycode == ESCM)
		return (handle_close(data));
	else
		return (get_keycode(keycode));
	return (0);
}
