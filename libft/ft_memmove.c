/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:10:10 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/24 18:44:57 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copie n octets depuis la zone mémoire src vers la
 * zone mémoire dest. Les deux zones  peuvent  se  chevaucher :  la  copie
 * s’effectue  comme  si  src  était  premièrement  copiée dans un tableau
 * temporaire ne chevauchant pas src ou dest puis il est copié vers  dest.
 *
 * Si src > dest: copier de gauche à droite (ft_memcpy)
 * Sinon copier de droite à gauche
 *
 * @return The original value of dst.
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*copiedst;
	char			*copiesrc;
	char			*tempdst;

	if (dst == 0 && src == 0)
		return (0);
	copiesrc = (char *)src;
	copiedst = (char *)dst;
	tempdst = copiedst;
	if (src > dst)
		ft_memcpy(tempdst, copiesrc, len);
	else
		while (len-- > 0)
			tempdst[len] = copiesrc[len];
	return (tempdst);
}
