/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:55:11 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/04 17:57:17 by bazaluga         ###   ########.fr       */
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
	{
		return (0);
	}
	if (j == -1 || j > 8)
	{
		color = ft_atou_base_forward(&line[3], "0123456789abcdef", &j);
		if (j == -1 || j > 8)
			return (0);
	}
	*i += j + 3;
	p->color = color;
	return (1);
}

static int	get_points_line(char *line, t_fdata *data, int y, int start)
{
	int		i;
	int		j;
	int		x;
	t_point	*arr;

	arr = data->pts.arr;
	i = 0;
	x = 0;
	while (line && line[i])
	{
		arr[start].k = ft_atoi_forward(&line[i], &j);
		if (j == -1)
			stop_error("Error trying to get the z value", data);
		arr[start].i = x;
		arr[start].j = y;
		arr[start].z = arr[start].k;
		if (!get_color(&line[i + j], &arr[start], &j))
			arr[start].color = 0xFFFFFF;
		i += j;
		start++;
		x++;
		while (line[i] && ft_isspace(line[i]))
			i++;
	}
	return (x);
}

int	parse_map(t_fdata *data)
{
	char		*line;
	int			row;
	int			res;
	int			prev_ncol;

	line = get_next_line(data->fd);
	row = 0;
	prev_ncol = 0;
	while (line)
	{
		if (data->pts.size == 0 || (row + 1) * prev_ncol > data->pts.size)
			dyn_alloc_point_arr(&data->pts, data);
		res = get_points_line(line, data, row, row * prev_ncol);
		free(line);
		if (!res || (prev_ncol != 0 && res != prev_ncol))
			stop_error("Wrong number of cols or other parsing problem", data);
		prev_ncol = res;
		line = get_next_line(data->fd);
		row++;
	}
	data->pts.r = row;
	data->pts.c = res;
	data->pts.size = row * res;
	normalize_coords(data, NULL);
	ft_printf("%d rows %d cols\n", row ,res);
	return (1);
}
