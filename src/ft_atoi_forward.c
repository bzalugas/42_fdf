/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_forward.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:17:00 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/21 12:24:36 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft/libft.h"

static int	get_nb(const char *nptr, char sign, int *i)
{
	int		res;
	long	n;
	int		check;

	n = 0;
	check = 0;
	while (nptr[*i] && ft_isdigit(nptr[*i]))
	{
		check = 1;
		n = n * 10 + (nptr[*i] - '0');
		(*i)++;
	}
	n *= sign;
	if (!check || n > INT_MAX || n < INT_MIN)
		*i = -1;
	res = (int)n;
	return (res);
}

int	ft_atoi_forward(const char *nptr, int *i)
{
	char	sign;

	*i = 0;
	while (nptr[*i] && ft_isspace(nptr[*i]))
		(*i)++;
	sign = 1;
	if (nptr[*i] && (nptr[*i] == '-' || nptr[*i] == '+'))
	{
		if (nptr[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (get_nb(&nptr[*i], sign, i));
}
