/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:55:11 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/21 23:35:19 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	get_color(char *line, t_point *p, int *i)
{
	int	color;
	int	j;

	if (!ft_strncmp(line, ",0x", 3))
		color = ft_atou_base_forward(&line[3], "0123456789ABCDEF", &j);
	else
		return (0);
	if (j == -1 || j > 8)
		return (0);
	*i += j + 3;
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
	p->h = z;
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
	p = NULL;
	while (line && line[i])
	{
		if (!new_point(&p, (t_point){0, x, n, 0, 0}, data))
			return (0);
		if (!get_pos(&line[i], p, &j))
			return (0);
		i += j;
		if (line[i] && line[i] == ',' && !get_color(&line[i], p, &i))
			return (0);
		if ((line[i] && !ft_isspace(line[i]))
			|| !ft_lstadd_back(pts, ft_lstnew2(p, &data->trash)))
			return (0);
		while (line[i] && ft_isspace(line[i]))
			i++;
		x++;
	}
	return (x);
}

static t_list	*get_points(int fd, t_fdata *data, int size[2])
{
	t_list	*points;
	char	*line;
	int		row;
	int		res;
	int		prev_ncol;

	line = get_next_line(fd);
	row = 0;
	points = NULL;
	prev_ncol = 0;
	while (line)
	{
		res = get_points_line(line, &points, data, row);
		free(line);
		if (!res || (prev_ncol != 0 && res != prev_ncol))
			stop_error("Error encountered while parsing the map", data);
		prev_ncol = res;
		line = get_next_line(fd);
		row++;
	}
	size[0] = row;
	size[1] = res;
	return (points);
}

t_point	***parse_map(t_fdata *data)
{
	t_list	*pts;
	t_list	*tmp;
	t_point	***arr;
	int		size[2];
	int		index[2];

	pts = get_points(data->fd, data, size);
	arr = alloc_point_arr(size[0], size[1], data);
	tmp = pts;
	index[0] = 0;
	while (tmp && index[0] < size[0])
	{
		index[1] = 0;
		while (tmp && index[1] < size[1])
		{
			arr[index[0]][index[1]] = (t_point *)tmp->content;
			tmp = tmp->next;
			index[1]++;
		}
		index[0]++;
	}
	ft_lstclear(&pts, NULL);
	return (arr);
}
