/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:54:35 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/17 14:11:38 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
