/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:12:06 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/21 23:34:24 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <fcntl.h>
#include "../include/mlx.h"
#include <errno.h>

void	print_points(t_list *points)
{
	t_list	*tmp;
	t_point	*p;

	if (!points)
		return ;
	tmp = points;
	p = (t_point *)tmp->content;
	while (tmp && tmp->content)
	{
		ft_printf("(%d,%d,%d)", p->x, p->y, p->z);
		tmp = tmp->next;
		if (tmp)
		{
			p = (t_point *)tmp->content;
			if (p->x == 0)
				write(1, "\n", 1);
			else
				write(1, " ", 1);
		}
	}
	write(1, "\n", 1);
}

void	print_pts(t_point ***pts)
{
	int	i;
	int	j;

	i = 0;
	while (pts[i])
	{
		j = 0;
		while (pts[i][j])
		{
			ft_printf("%d", pts[i][j]->h);
			if (pts[i][j + 1])
				write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

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
	t_fdata	d;
	t_point	***pts;

	if (ac != 2)
		stop_perror("Please provide a valid file name as argument", &d, EINVAL);
	check_name(av[1]);
	d = (t_fdata){(t_img){0}, NULL, NULL, -1, NULL};
	d.fd = open(av[1], O_RDONLY);
	if (d.fd == -1)
		stop_perror("Error while opening given file name", &d, 0);
	pts = parse_map(&d);
	close(d.fd);
	d.fd = -1;
	print_pts(pts);
	end_fdf(&d, 0);
	return (0);
}
