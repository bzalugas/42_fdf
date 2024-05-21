/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:28:24 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/21 13:49:23 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_list	*ft_lstnew2(void *content, t_list **trash)
{
	t_list	*new;

	new = (t_list *)ft_mylloc(sizeof(t_list), trash);
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
