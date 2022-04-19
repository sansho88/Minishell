/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:48 by tgriffit          #+#    #+#             */
/*   Updated: 2022/04/19 18:01:28 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftminitalk.h"

/*si l'espace mémoire libre qui suit le bloc à réallouer est suffisament
	 * grand, le bloc de mémoire est simplement agrandi. Par contre si l'espace
	 * libre n'est pas suffisant, un nouveau bloc de mémoire sera alloué,
	 * le contenu de la zone d'origine recopié dans la nouvelle zone et le bloc
	 * mémoire d'origine sera libéré automatiquement.*/
void	*ft_realloc(void *ptr, size_t newsize)
{
	char		*res;
	size_t		oldsize;

	oldsize = ft_strlen(ptr);
	if (newsize <= oldsize)
		return (ptr);
	res = ft_memalloc(newsize);
	if (!res)
		return (0);
	if (oldsize > 0)
		ft_memcpy(res, ptr, oldsize);
	ft_memdel(&ptr);
	return (res);
}
//TODO: strdup_cat(char *dst, char *src) (free dst apres copie puis renvoyer new dest)

//TODO: Integrer calloc dans la lib