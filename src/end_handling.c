/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:39:16 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/23 15:51:48 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/mlx.h"
#include <errno.h>
#include <stdio.h>

int	end_fdf(t_fdata *data, int exit_code)
{
	if (data)
	{
		if (data->img.ptr)
			mlx_destroy_image(data->mlx, data->img.ptr);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		if (data->mlx)
			mlx2_destroy_display(data->mlx);
		if (data->fd != -1)
			close(data->fd);
		ft_empty_trash(&data->trash);
	}
	exit(exit_code);
}

int	stop_perror(char *msg, t_fdata *data, int error)
{
	if (error != 0)
		errno = error;
	perror(msg);
	end_fdf(data, errno);
	exit(error);
}

int	stop_error(char *msg, t_fdata *data)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	end_fdf(data, EXIT_FAILURE);
	exit(EXIT_FAILURE);
}
