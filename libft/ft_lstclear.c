/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:50:51 by tgriffit          #+#    #+#             */
/*   Updated: 2022/04/19 18:05:26 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Supprime et libère la mémoire de l’élément passé en paramètre,
 * et de tous les élements qui suivent, à l’aide de del et de free(3).\n
 * Enfin, le pointeur initial doit être mis à NULL.
 * @param lst
 * @param del
 */
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;
	t_list	*temp;

	if (!lst || !del)
		return ;
	temp = *lst;
	while (temp)
	{
		next = temp->next;
		ft_lstdelone(temp, del);
		temp = next;
	}
	*lst = 0;
}
