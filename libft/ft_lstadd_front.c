/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:43:02 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/24 16:11:29 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Add the "new" element at the beginning of the list.
 * @param alst = Pointer address of the first list's element
 * @param new = Pointer address of the element to add to the list
 */
void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (!alst)
		return ;
	if (new)
	{
		new->next = *alst;
		*alst = new;
	}
}
