/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:58:23 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/31 18:44:58 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <math.h>

void	rotate_x(t_point *p, float angle)
{
	int	y2;
	int	z2;

	y2 = round(cos(angle) * (float)p->y - sin(angle) * (float)p->z);
	z2 = round(sin(angle) * (float)p->y + cos(angle) * (float)p->z);
	p->y = y2;
	p->z = z2;
	ft_printf("new coords = (%d,%d,%d)\n", p->x, p->y, p->z);
}

void	rotate_y(t_point *p, float angle)
{
	int	x2;
	int	z2;

	x2 = round(cos(angle) * (float)p->x + sin(angle) * (float)p->z);
	z2 = round(-sin(angle) * (float)p->x + cos(angle) * (float)p->z);
	p->x = x2;
	p->z = z2;
	ft_printf("new coords = (%d,%d,%d)\n", p->x, p->y, p->z);
}
