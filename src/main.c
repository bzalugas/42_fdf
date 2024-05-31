/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:12:06 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/31 13:07:37 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <fcntl.h>
#include <errno.h>

static int	check_name(char *s)
{
	size_t	i;

	i = ft_strlen(s);
	if (!(i > 4 && !ft_strncmp(&s[i - 4], ".fdf", 4)))
		stop_perror("The map should have the .fdf extension", NULL, EINVAL);
	return (1);
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
