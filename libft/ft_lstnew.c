/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:34:46 by tgriffit          #+#    #+#             */
/*   Updated: 2022/05/13 11:37:33 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Alloue (avec malloc(3)) et renvoie un nouvel élément. la variable content
 * est initialisée à l’aide de la valeur du paramètre content. La
 * variable ’next’ est initialisée à NULL.
 * @param content = Le contenu du nouvel élément.
 * @return Le nouvel element
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*res;

	res = malloc(sizeof(t_list));
	if (!res)
		return (0);
	res -> content = content;
	res -> next = 0;
	return (res);
}
