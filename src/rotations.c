/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:58:23 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/13 14:44:38 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <math.h>

void	rotate_x(t_point *p, float angle)
{
	double	y2;
	double	z2;

	y2 = cos(angle) * p->y - sin(angle) * p->z;
	z2 = sin(angle) * p->y + cos(angle) * p->z;
	p->y = y2;
	p->z = z2;
}

void	rotate_y(t_point *p, float angle)
{
	double	x2;
	double	z2;

	x2 = cos(angle) * p->x + sin(angle) * p->z;
	z2 = -sin(angle) * p->x + cos(angle) * p->z;
	p->x = x2;
	p->z = z2;
}

void	rotate_z(t_point *p, float angle)
{
	double	x2;
	double	y2;

	x2 = cos(angle) * p->x - sinf(angle) * p->y;
	y2 = sin(angle) * p->x + cosf(angle) * p->y;
	p->x = x2;
	p->y = y2;
}

void	rotate_img(t_fdata *d, int axis, bool from_start)
{
	int		i;
	void	(*fun[3])(t_point *, float);
	float	angle[3];

	fun[AXIS_X] = rotate_x;
	angle[AXIS_X] = ft_rad(d->img.rx);
	fun[AXIS_Y] = rotate_y;
	angle[AXIS_Y] = ft_rad(d->img.ry);
	fun[AXIS_Z] = rotate_z;
	angle[AXIS_Z] = ft_rad(d->img.rz);
	i = 0;
	while (i < d->pts.size)
	{
		if (from_start)
		{
			// USE SCALE MATRIX ?
			d->pts.arr[i].x = d->pts.arr[i].i * d->img.sp;
			d->pts.arr[i].y = d->pts.arr[i].j * d->img.sp;
			d->pts.arr[i].z = d->pts.arr[i].k * d->img.sp / 8;
		}
		fun[axis](&d->pts.arr[i], angle[axis]);
		i++;
	}
	d->img.normalized = false;
}
