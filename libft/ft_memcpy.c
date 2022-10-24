/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:52:23 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/24 17:17:37 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**The memcpy() function copies n bytes from memory area src to memory area dst.
 * If dst and src overlap, behavior is undefined.
 * Applications in which dst and src might overlap
 * should use memmove(3) instead. */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*resdst;
	char		*ressrc;

	if (dst == 0 && src == 0)
		return (0);
	resdst = (char *)dst;
	ressrc = (char *)src;
	i = 0;
	while (i < n)
	{
		resdst[i] = ressrc[i];
		i++;
	}
	return (resdst);
}
