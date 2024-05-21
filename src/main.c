/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:12:06 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/21 15:48:25 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <stdio.h>
#include <fcntl.h>
#include "../include/mlx.h"
#include <errno.h>

int	end_fdf(t_fdata *data, int exit_code)
{
	if (data->img.ptr)
		mlx_destroy_image(data->mlx, data->img.ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx2_destroy_display(data->mlx);
	ft_empty_trash(&data->trash);
	exit(exit_code);
}

int	stop_error(char *msg, t_fdata *data, int error)
{
	errno=error;
	perror(msg);
	end_fdf(data, EXIT_FAILURE);
	exit(EXIT_FAILURE);
}

void	print_points(t_list *points)
{
	t_list	*tmp;
	t_point	*p;

	tmp = points;
	p = (t_point *)tmp->content;
	while (tmp && tmp->content)
	{
		ft_printf("(%d,%d,%d)", p->x, p->y, p->z);
		tmp = tmp->next;
		p = (t_point *)tmp->content;
		if (p->x == 0)
			write(1, "\n", 1);
		else
			write(1, " ", 1);
	}
}

int	main(int ac, char *av[])
{
	t_fdata	data;
	/* t_point	***points; */
	t_list	*pts;
	int		fd;

	if (ac != 2)
		stop_error("Please provide a valid file name as argument", &data, );
	data = (t_fdata){0};
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		stop_error("Error while opening given file name", &data, 5);
	pts = parse_map(fd, &data);
	close(fd);
	print_points(pts);
	return (0);
}
