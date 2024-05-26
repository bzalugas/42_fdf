/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:49:36 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/06 23:02:07 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	*ft_max_arr(int *arr, size_t len)
{
	size_t	i;
	int		*max;

	if (!arr)
		return ((void *)0);
	max = &arr[0];
	i = 1;
	while (i < len)
	{
		if (arr[i] > *max)
			max = &arr[i];
		i++;
	}
	return (max);
}
