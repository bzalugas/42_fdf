/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:38:44 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/13 19:25:54 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/libft/libft.h"

void	*ft_mylloc(size_t size, t_list **garbage)
{
	void	*addr;

	addr = malloc(size);
	ft_lstadd_back(garbage, ft_lstnew(addr));
	return (addr);
}

void	*ft_cylloc(size_t nmemb, size_t size, t_list **garbage)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, size);
	ft_lstadd_back(garbage, ft_lstnew(ptr));
	return (ptr);
}

void	ft_empty_trash(t_list **garbage)
{
	ft_lstclear(garbage, free);
}
