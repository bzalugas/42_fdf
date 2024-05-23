/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:33:10 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/23 14:03:24 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_point	*new_point(t_point **res, t_point p, t_fdata *data)
{
	t_point	*point;

	point = (t_point *)ft_cylloc(1, sizeof(t_point), &data->trash);
	if (!point)
		return (NULL);
	*point = p;
	*res = point;
	return (point);
}

t_point	**alloc_point_arr(t_pts_arr *pts, t_fdata *d)
{
	t_point	**arr;

	arr = (t_point **)ft_cylloc(pts->size + 1, sizeof(t_point *), &d->trash);
	if (!arr)
		stop_error("Error while creating points array", d);
	return (arr);
}
