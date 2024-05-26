/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:12:06 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/26 21:44:09 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <stdio.h>
#include <fcntl.h>
#include "../include/mlx.h"
#include <errno.h>

static int	check_name(char *s)
{
	size_t	i;

	i = ft_strlen(s);
	if (!(i > 4 && !ft_strncmp(&s[i - 4], ".fdf", 4)))
		stop_perror("The map should have the .fdf extension", NULL, EINVAL);
	return (1);
}

static void	config_img(t_fdata *d)
{
	d->img.spx = WIDTH / d->pts.c;
	d->img.spy = HEIGHT / d->pts.r;
	if (d->img.spx < DEFAULT_SPACE)
		d->img.spx = DEFAULT_SPACE;
	if (d->img.spy < DEFAULT_SPACE)
		d->img.spy = DEFAULT_SPACE;
	d->img.offset = DEFAULT_OFFSET;
	d->img.scale = DEFAULT_SCALE;
}
int	refresh_display(t_fdata *d);
static void	display(t_fdata *d)
{
	d->mlx = mlx_init();
	if (!d->mlx)
		stop_error("Error at mlx initialization", d);
	config_img(d);
	d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "FdF");
	if (!d->win)
		stop_error("Error at mlx window initialization", d);
	/* put_points(d); */
	mlx_loop_hook(d->mlx, &refresh_display, d);
	mlx_hook(d->win, DESTROY, 0, &handle_close, d);
	mlx_hook(d->win, KEYDOWN, 1L << 0, &handle_key, d);
	mlx_loop(d->mlx);
}

int	main(int ac, char *av[])
{
	t_fdata		d;

	d = (t_fdata){NULL, NULL, (t_img){0}, (t_pts_arr){0}, -1, NULL};
	if (ac != 2)
		stop_perror("Please provide a valid file name as argument", &d, EINVAL);
	check_name(av[1]);
	d.fd = open(av[1], O_RDONLY);
	if (d.fd == -1)
		stop_perror("Error while opening given file name", &d, 0);
	parse_map(&d);
	close(d.fd);
	d.fd = -1;
	display(&d);
	end_fdf(&d, 0);
	return (0);
}
