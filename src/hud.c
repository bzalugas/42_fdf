/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:33:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/13 18:59:39 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"

void	dynamic_hud(t_fdata *d)
{
	char	*rots[3];
	char	*txts[3];
	int		index[2];

	mlx_string_put(d->mlx, d->win, 10, 215, 0xF4E7FD,
		"_____________INFO_____________");
	index[0] = 220;
	while (index[0] < 265)
	{
		index[1] = 80;
		while (index[1] < 130)
		{
			mlx_pixel_put(d->mlx, d->win, index[1], index[0], 0x0);
			index[1]++;
		}
		index[0]++;
	}
	rots[0] = ft_ftoa(d->img.rx, 3);
	rots[1] = ft_ftoa(d->img.ry, 3);
	rots[2] = ft_ftoa(d->img.rz, 3);
	txts[0] = ft_strjoin("Rotation X: ", rots[0]);
	txts[1] = ft_strjoin("Rotation Y: ", rots[1]);
	txts[2] = ft_strjoin("Rotation Z: ", rots[2]);
	free(rots[0]);
	free(rots[1]);
	free(rots[2]);
	mlx_string_put(d->mlx, d->win, 10, 230, 0xF4E7FD, txts[0]);
	mlx_string_put(d->mlx, d->win, 10, 245, 0xF4E7FD, txts[1]);
	mlx_string_put(d->mlx, d->win, 10, 260, 0xF4E7FD, txts[2]);
	free(txts[0]);
	free(txts[1]);
	free(txts[2]);

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
