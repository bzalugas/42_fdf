/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:33:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/06 12:31:57 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"

void	dynamic_hud(t_fdata *d)
{
	mlx_string_put(d->mlx, d->win, 10, 200, 0xF4E7FD,
		"_____________INFO_____________");

}

void	display_hud(t_fdata *d)
{
	mlx_string_put(d->mlx, d->win, 50, 10, 0xF4E7FD, "KEYMAPS");
	mlx_string_put(d->mlx, d->win, 10, 30, 0xF4E7FD, "Change mode:      SPACE");
	mlx_string_put(d->mlx, d->win, 10, 45, 0xF4E7FD, "Altitude:         J,K");
	mlx_string_put(d->mlx, d->win, 10, 60, 0xF4E7FD, "Automatic colors: C");
	mlx_string_put(d->mlx, d->win, 10, 75, 0xF4E7FD,
		"_________Rotation mode_________");
	mlx_string_put(d->mlx, d->win, 10, 90, 0xF4E7FD, "X rotations:     W,S");
	mlx_string_put(d->mlx, d->win, 10, 105, 0xF4E7FD, "Y rotations:     A,D");
	mlx_string_put(d->mlx, d->win, 10, 120, 0xF4E7FD, "Z rotations:     Q,E");
	mlx_string_put(d->mlx, d->win, 10, 135, 0xF4E7FD,
		"_______Translation mode_______");
	mlx_string_put(d->mlx, d->win, 10, 150, 0xF4E7FD, "X translations:  A,D");
	mlx_string_put(d->mlx, d->win, 10, 165, 0xF4E7FD, "Y translations:  W,D");
	dynamic_hud(d);
}
