/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:55:11 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/21 14:06:47 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	get_color(char *line, t_point *p, int *j)
{
	int	color;

	color = ft_atoi_forward(line, j);
	if (*j == -1)
		return (0);
	p->color = color;
	return (1);
}

static int	get_pos(char *line, t_point *p, int *j)
{
	int	z;

	z = ft_atoi_forward(line, j);
	if (*j == -1)
		return (0);
	p->z = z;
	return (1);
}

static int	get_points_line(char *line, t_list **pts, t_fdata *data, int n)
{
	int		i;
	int		j;
	int		x;
	t_point	*p;

	i = 0;
	x = 0;
	while (line && line[i])
	{
		if (!new_point(&p, (t_point){0, x, n, 0, 0}, data))
			return (0);
		if (!get_pos(&line[i], p, &j))
			return (0);
		i += j;
		if (line[i] && line[i] == ',' && !get_color(&line[i + 1], p, &j))
			return (0);
		i += j;
		if ((line[i] && !ft_isspace(line[i])) ||
			!ft_lstadd_back(pts, ft_lstnew2(p, &data->trash)))
			return (0);
		while (line[i] && ft_isspace(line[i]))
			i++;
		x++;
	}
	return (1);
}

t_list	*parse_map(int fd, t_fdata *data)
{
	t_list	*points;
	char	*line;
	int		nline;

	line = get_next_line(fd);
	nline = 0;
	while (line)
	{
		get_points_line(line, &points, data, nline);
		free(line);
		line = get_next_line(fd);
		nline++;
	}
	return (points);
}
