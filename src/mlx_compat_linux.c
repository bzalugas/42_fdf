/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_compat_linux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:13:51 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/20 17:31:16 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx_linux/mlx_int.h"
#include "../include/mlx.h"

int	mlx2_destroy_display(t_xvar *xvar)
{
	mlx_destroy_display(xvar);
	free(xvar);
	return (1);
}
