/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:33:10 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/21 13:58:27 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_point	*new_point(t_point **res, t_point p, t_fdata *data)
{
	t_point	*point;

	point = ft_cylloc(1, sizeof(t_point *), &data->garbage);
	*point = p;
	return (point);
}
