/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:38:44 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/21 23:33:40 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/libft/libft.h"

void	*ft_mylloc(size_t size, t_list **trash)
{
	void	*addr;

	addr = malloc(size);
	if (!ft_lstadd_back(trash, ft_lstnew(addr)))
		return (NULL);
	return (addr);
}

void	*ft_cylloc(size_t nmemb, size_t size, t_list **trash)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, size);
	if (!ft_lstadd_back(trash, ft_lstnew(ptr)))
		return (NULL);
	return (ptr);
}

void	*ft_add_garbage(t_list **trash, void *ptr)
{
	t_list	*garbage;

	if (!trash)
		return (NULL);
	garbage = ft_lstnew(ptr);
	if (!ft_lstadd_back(trash, garbage))
		return (NULL);
	return (garbage);
}

void	ft_empty_trash(t_list **trash)
{
	ft_lstclear(trash, free);
}
