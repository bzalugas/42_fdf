/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:01:15 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/23 15:53:23 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"

int	handle_close(t_fdata *data)
{
	end_fdf(data, 0);
	exit(0);
}

int	handle_key(int keycode, t_fdata *data)
{
	if (keycode == ESC || keycode == ESCM)
		return (handle_close(data));
	return (0);
}
