/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:51:43 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/06 23:02:19 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	*ft_min_arr(int *arr, size_t len)
{
	size_t	i;
	int		*min;

	if (!arr)
		return ((void *)0);
	min = &arr[0];
	i = 1;
	while (i < len)
	{
		if (arr[i] < *min)
			min = &arr[i];
		i++;
	}
	return (min);
}
