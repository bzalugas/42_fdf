/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:33:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/14 14:15:34 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"

static void	reset_chunk(t_fdata *d)
{
	mlx_string_put(d->mlx, d->win, 10, 230, 0x0, d->txts[0]);
	mlx_string_put(d->mlx, d->win, 10, 245, 0x0, d->txts[1]);
	mlx_string_put(d->mlx, d->win, 10, 260, 0x0, d->txts[2]);
	mlx_string_put(d->mlx, d->win, 10, 275, 0x0, d->txts[3]);
	mlx_string_put(d->mlx, d->win, 10, 290, 0x0, d->txts[4]);
	ft_free_garbage(d->txts[0], &d->trash);
	ft_free_garbage(d->txts[1], &d->trash);
	ft_free_garbage(d->txts[2], &d->trash);
	ft_free_garbage(d->txts[3], &d->trash);
	ft_free_garbage(d->txts[4], &d->trash);
}

static void	dynamic_hud2(t_fdata *d)
{
	char	*rots[3];

	rots[0] = ft_ftoa(d->img.rx, 3);
	rots[1] = ft_ftoa(d->img.ry, 3);
	rots[2] = ft_ftoa(d->img.rz, 3);
	d->txts[2] = ft_strjoin("Rotation X: ", rots[0]);
	d->txts[3] = ft_strjoin("Rotation Y: ", rots[1]);
	d->txts[4] = ft_strjoin("Rotation Z: ", rots[2]);
	ft_add_garbage(&d->trash, d->txts[2]);
	ft_add_garbage(&d->trash, d->txts[3]);
	ft_add_garbage(&d->trash, d->txts[4]);
	free(rots[0]);
	free(rots[1]);
	free(rots[2]);
	mlx_string_put(d->mlx, d->win, 10, 230, 0xF4E7FD, d->txts[0]);
	mlx_string_put(d->mlx, d->win, 10, 245, 0xF4E7FD, d->txts[1]);
	mlx_string_put(d->mlx, d->win, 10, 260, 0xF4E7FD, d->txts[2]);
	mlx_string_put(d->mlx, d->win, 10, 275, 0xF4E7FD, d->txts[3]);
	mlx_string_put(d->mlx, d->win, 10, 290, 0xF4E7FD, d->txts[4]);
}

void	dynamic_hud(t_fdata *d, bool first)
{
	mlx_string_put(d->mlx, d->win, 10, 215, 0xF4E7FD,
		"_____________INFO_____________");
	if (!first)
		reset_chunk(d);
	if (d->img.rot_mode == 1)
		d->txts[0] = ft_strjoin("Movement:   ", "ROTATIONS");
	else
		d->txts[0] = ft_strjoin("Movement:   ", "TRANSLATIONS");
	if (d->img.projection == 1)
		d->txts[1] = ft_strjoin("Projection: ", "ISOMETRIC");
	else
		d->txts[1] = ft_strjoin("Projection: ", "MULTIVIEW");
	ft_add_garbage(&d->trash, d->txts[0]);
	ft_add_garbage(&d->trash, d->txts[1]);
	dynamic_hud2(d);
}

void	display_hud(t_fdata *d)
{
	mlx_string_put(d->mlx, d->win, 50, 10, 0xF4E7FD, "KEYMAPS");
	mlx_string_put(d->mlx, d->win, 10, 30, 0xF4E7FD, "Change mode:      SPACE");
	mlx_string_put(d->mlx, d->win, 10, 45, 0xF4E7FD, "Altitude:         J,K");
	mlx_string_put(d->mlx, d->win, 10, 60, 0xF4E7FD, "Automatic colors: C");
	mlx_string_put(d->mlx, d->win, 10, 75, 0xF4E7FD, "Toggle lines:     L");
	mlx_string_put(d->mlx, d->win, 10, 90, 0xF4E7FD,
		"_________Rotation mode_________");
	mlx_string_put(d->mlx, d->win, 10, 105, 0xF4E7FD, "X rotations:     W,S");
	mlx_string_put(d->mlx, d->win, 10, 120, 0xF4E7FD, "Y rotations:     A,D");
	mlx_string_put(d->mlx, d->win, 10, 135, 0xF4E7FD, "Z rotations:     Q,E");
	mlx_string_put(d->mlx, d->win, 10, 150, 0xF4E7FD,
		"_______Translation mode_______");
	mlx_string_put(d->mlx, d->win, 10, 165, 0xF4E7FD, "X translations:  A,D");
	mlx_string_put(d->mlx, d->win, 10, 180, 0xF4E7FD, "Y translations:  W,S");
	mlx_string_put(d->mlx, d->win, 10, 200, 0xF4E7FD, "Reset:           R");
	dynamic_hud(d, true);
}
