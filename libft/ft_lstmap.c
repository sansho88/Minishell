/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:18:26 by tgriffit          #+#    #+#             */
/*   Updated: 2022/05/13 11:37:33 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Itère sur la liste lst et applique la fonction f au contenu de chaque
 * élément. Crée une nouvelle liste résultant des applications successives
 * de f.\n
 * la fonction del est là pour detruire le contenu d'un element si necessaire.
 * @param lst = L’adresse du pointeur vers un élément.
 * @param f = L’adresse de la fonction à appliquer.
 * @param del = L’adresse de la fonction del à appliquer si necessaire.
 * @return
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstres;
	t_list	*new;

	if (!lst || !f)
		return (0);
	new = ft_lstnew(f(lst->content));
	lstres = new;
	while (lst->next)
	{
		lst = lst->next;
		new->next = ft_lstnew(f(lst->content));
		if (!new->next)
		{
			ft_lstdelone(new->next, del);
			return (0);
		}
		new = new->next;
	}
	return (lstres);
}
