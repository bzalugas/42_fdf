/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:32:20 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/06 19:26:12 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	n_size(long int_part)
{
	size_t	size;

	size = 1;
	while (int_part > 9)
	{
		size++;
		int_part /= 10;
	}
	return (size);
}

static void	convert(char *res, double n, unsigned long int_part, size_t *sizes)
{
	size_t	i;

	i = sizes[0] - sizes[1];
	n -= int_part;
	while (sizes[0] > 0 && n > 0.0 && sizes[1] > 0)
	{
		n *= 10;
		res[i] = (int)n + '0';
		n -= (int)n;
		i++;
		sizes[1]--;
		sizes[0]--;
	}
	res[--sizes[0]] = '.';
	while (sizes[0] > 0)
	{
		res[sizes[0] - 1] = int_part % 10 + '0';
		int_part /= 10;
		sizes[0]--;
	}
}

char	*ft_ftoa(double n, int precision)
{
	double	int_part;
	int		neg;
	size_t	sizes[2];
	char	*res;

	sizes[1] = precision;
	neg = 0;
	if (n < 0 && ++neg)
		n *= -1;
	int_part = (unsigned long)n;
	sizes[0] = n_size(int_part);
	sizes[0] += neg + precision + 1;
	res = (char *)calloc(sizes[0] + 1, sizeof(char));
	if (!res)
		return (NULL);
	convert(res, n, int_part, sizes);
	if (neg)
		res[0] = '-';
	return (res);
}
