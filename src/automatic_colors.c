/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automatic_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:28:10 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/14 15:11:34 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <math.h>

void	reset_colors(t_fdata *d)
{
	size_t	i;

	i = 0;
	while (i < d->pts.size)
	{
		d->pts.arr[i].color = d->pts.arr[i].color2;
		i++;
	}
}

static void	set_colors(int steps_up[3], int steps_down[3], t_fdata *d)
{
	size_t	i;

	i = 0;
	while (i < d->pts.size)
	{
		if (d->pts.arr[i].k * d->img.elev == 0)
			d->pts.arr[i].color = POS0;
		else if (d->pts.arr[i].k * d->img.elev >= steps_up[2])
			d->pts.arr[i].color = POS4;
		else if (d->pts.arr[i].k * d->img.elev >= steps_up[1])
			d->pts.arr[i].color = POS3;
		else if (d->pts.arr[i].k * d->img.elev >= steps_up[0])
			d->pts.arr[i].color = POS2;
		else if (d->pts.arr[i].k * d->img.elev > 5)
			d->pts.arr[i].color = POS1;
		else if (d->pts.arr[i].k * d->img.elev <= steps_down[2])
			d->pts.arr[i].color = NEG3;
		else if (d->pts.arr[i].k * d->img.elev <= steps_down[1])
			d->pts.arr[i].color = NEG2;
		else if (d->pts.arr[i].k * d->img.elev <= steps_down[0])
			d->pts.arr[i].color = NEG1;
		else
			d->pts.arr[i].color = POS0;
		i++;
	}
}

void	auto_colors(t_fdata *d)
{
	size_t	i;
	int		max_alt;
	int		min_alt;
	int		steps_up[3];
	int		steps_down[3];

	max_alt = d->pts.arr[0].k;
	min_alt = max_alt;
	i = 1;
	while (i < d->pts.size)
	{
		if (d->pts.arr[i].k * d->img.elev > max_alt)
			max_alt = d->pts.arr[i].k * d->img.elev;
		else if (d->pts.arr[i].k * d->img.elev < min_alt)
			min_alt = d->pts.arr[i].k * d->img.elev;
		i++;
	}
	steps_up[0] = round(0.2 * max_alt);
	steps_up[1] = max_alt / 2;
	steps_up[2] = round(0.75 * max_alt);
	steps_down[0] = round(0.2 * min_alt);
	steps_down[1] = round(0.5 * min_alt);
	steps_down[2] = round(0.75 * min_alt);
	set_colors(steps_up, steps_down, d);
}
