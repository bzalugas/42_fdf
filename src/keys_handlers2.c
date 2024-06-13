/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handlers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:58:36 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/13 15:08:51 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	change_elevation(t_fdata *d, int key)
{
	if (key == KEY_J)
		d->img.elev += 0.5;
	else if (key == KEY_K)
		d->img.elev -= 0.5;
	rotate_img(d, AXIS_Y, true);
	rotate_img(d, AXIS_Z, false);
	rotate_img(d, AXIS_X, false);
	d->img.refresh = true;
}
