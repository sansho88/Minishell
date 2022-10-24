/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:21:49 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/24 17:17:37 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * Libère la mémoire de l’élément passé en argument en utilisant
 * la fonction del puis avec free(3). La mémoire de next ne doit pas être free.
 * @param lst = l'élément à supprimer
 * @param del = l'adresse de la fonction de suppression du contenu de l'élément
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !lst->content || !del)
		return ;
	del(lst->content);
	free(lst);
}
