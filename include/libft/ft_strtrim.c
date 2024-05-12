/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:48:20 by bazaluga          #+#    #+#             */
/*   Updated: 2023/11/26 00:59:26 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = (char *)s1;
	while (*start && ft_strchr(set, *start))
		start++;
	if (!*start)
		return (ft_strdup(""));
	end = start + ft_strlen(start);
	while (end > start && ft_strchr(set, *end))
		end--;
	len = (end - start) + 1;
	return (ft_strndup(start, len));
}
