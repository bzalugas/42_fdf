/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:51:14 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/13 18:53:52 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return ;
	dst = img->addr + (x * (img->bpp / 8) + y * img->size);
	*(unsigned int *)dst = color;
}

void	init_pixels_arr(t_fdata *d)
{
	size_t	i;
	size_t	size;

	size = HEIGHT * WIDTH;
	i = 0;
	while (i < size)
	{
		d->img.ptslines[i] = (t_ptline){0};
		i++;
	}
}

bool	is_infront(int xy[2], t_ptline *ptl, t_fdata *d)
{
	t_ptline	*actual;

	if (xy[0] >= WIDTH || xy[0] < 0 || xy[1] >= HEIGHT || xy[1] < 0)
		return (false);
	actual = &d->img.ptslines[WIDTH * xy[1] + xy[0]];
	if (!actual->draw
		|| (actual->draw && actual->z0 < ptl->z0 && actual->z1 < ptl->z1))
	{
		*actual = *ptl;
		return (true);
	}
	return (false);
}

bool	pt_infront(t_point *p, t_fdata *d)
{
	t_ptline	*actual;

	actual = &d->img.ptslines[WIDTH * (int)p->y + (int)p->x];
	if (!actual->draw
		|| (actual->draw && actual->z0 < p->z))
	{
		*actual = (t_ptline){true, p->z, p->z};
		return (true);
	}
	return (false);
}
