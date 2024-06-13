/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:33:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/13 21:11:24 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"

static void	dynamic_hud2(t_fdata *d, char *txts[5])
{
	char	*rots[3];

	rots[0] = ft_ftoa(d->img.rx, 3);
	rots[1] = ft_ftoa(d->img.ry, 3);
	rots[2] = ft_ftoa(d->img.rz, 3);
	txts[2] = ft_strjoin("Rotation X: ", rots[0]);
	txts[3] = ft_strjoin("Rotation Y: ", rots[1]);
	txts[4] = ft_strjoin("Rotation Z: ", rots[2]);
	free(rots[0]);
	free(rots[1]);
	free(rots[2]);
	mlx_string_put(d->mlx, d->win, 10, 230, 0xF4E7FD, txts[0]);
	mlx_string_put(d->mlx, d->win, 10, 245, 0xF4E7FD, txts[1]);
	mlx_string_put(d->mlx, d->win, 10, 260, 0xF4E7FD, txts[2]);
	mlx_string_put(d->mlx, d->win, 10, 275, 0xF4E7FD, txts[3]);
	mlx_string_put(d->mlx, d->win, 10, 290, 0xF4E7FD, txts[4]);
	free(txts[0]);
	free(txts[1]);
	free(txts[2]);
	free(txts[3]);
	free(txts[4]);
}

static void	reset_chunk(t_fdata *d, int cols[2], int rows[2])
{
	int	x;
	int	y;

	y = cols[0];
	while (y < cols[1])
	{
		x = rows[0];
		while (x < rows[1])
		{
			mlx_pixel_put(d->mlx, d->win, x, y, 0x0);
			x++;
		}
		y++;
	}
}

void	dynamic_hud(t_fdata *d)
{
	//Optimize this one
	char	*txts[5];
	char	*modes[2];

	mlx_string_put(d->mlx, d->win, 10, 215, 0xF4E7FD,
		"_____________INFO_____________");
	reset_chunk(d, (int[2]){220, 290}, (int[2]){80, 160});
	if (d->img.rot_mode == 1)
		modes[0] = ft_strdup("ROTATIONS");
	else
		modes[0] = ft_strdup("TRANSLATIONS");
	if (d->img.projection == 1)
		modes[1] = ft_strdup("ISOMETRIC");
	else
		modes[1] = ft_strdup("MULTIVIEW");
	txts[0] = ft_strjoin("Movement:   ", modes[0]);
	txts[1] = ft_strjoin("Projection: ", modes[1]);
	free(modes[0]);
	free(modes[1]);
	dynamic_hud2(d, txts);
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
	dynamic_hud(d);
}
