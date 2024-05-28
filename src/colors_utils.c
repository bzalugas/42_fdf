/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:32:08 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/28 20:14:13 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <math.h>

/*
** Convert 4 values of a color to an int
** Returns: the int representing the color
*/
int	trgb_to_i(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*
** Convert an int representing a color to 4 values (trgb)
** Set by reference r,g,b part of color
** Returns: transparency part of color
*/
int	i_to_trgb(int color, int *r, int *g, int *b)
{
	if (r)
		*r = (color >> 16) & 0xFF;
	if (g)
		*g = (color >> 8) & 0xFF;
	if (b)
		*b = color & 0xFF;
	return ((color >> 24) & 0xFF);
}

int	gradient(int c0, int c1, float distance, int ipixel)
{
	int		res[3];
	int		p0cols[3];
	int		p1cols[3];
	float	value;

	if (c0 == c1)
		return (c0);
	value = (float)((1 / distance) * (float)ipixel);
	i_to_trgb(c0, &p0cols[0], &p0cols[1], &p0cols[2]);
	i_to_trgb(c1, &p1cols[0], &p1cols[1], &p1cols[2]);
	res[0] = p0cols[0] + round((p1cols[0] - p0cols[0]) * value);
	res[1] = p0cols[1] + round((p1cols[1] - p0cols[1]) * value);
	res[2] = p0cols[2] + round((p1cols[2] - p0cols[2]) * value);
	return (trgb_to_i(0, res[0], res[1], res[2]));
}

/* void	test_gradient(void) */
/* { */
/* 	int	c0[4]; */
/* 	int	c1[4]; */
/* 	int	res[4]; */

/* 	c0[0] = 0xff0000; */
/* 	c1[0] = 0x0000ff; */
/* 	i_to_trgb(c0[0], &c0[1], &c0[2], &c0[3]); */
/* 	i_to_trgb(c1[0], &c1[1], &c1[2], &c1[3]); */
/* 	ft_printf("from (%d,%d,%d) to (%d,%d,%d)\n", c0[1], c0[2], c0[3],
 * 	c1[1], c1[2], c1[3]); */
/* 	for (int i = 0; i < 10; i++) */
/* 	{ */
/* 		res[0] = gradient(c0[0], c1[0], 10, i); */
/* 		i_to_trgb(res[0], &res[1], &res[2], &res[3]); */
/* 		ft_printf("%d: (%d,%d,%d)\n", i, res[1], res[2], res[3]); */
/* 	} */
/* 	exit(0); */
/* } */
