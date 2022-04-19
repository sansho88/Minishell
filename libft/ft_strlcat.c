/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:29:54 by tgriffit          #+#    #+#             */
/*   Updated: 2021/11/11 15:08:02 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Concatenate strings. It takes the full size of the destination buffer and
 * guarantee NUL-termination if there is room.  Note that room for the NUL
 * should be included in dstsize.
 * @param dst = The future string modified
 * @param src = string to add to dst
 * @param dstsize = Size of actual dst (ex: ft_strlen(dst))
 * @return The total length of the string it tried to create (dst + src lenghts)
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	j = i;
	while (src[i - j] && i < dstsize - 1)
	{
		dst[i] = src[i - j];
		i++;
	}
	if (j < dstsize)
		dst[i] = '\0';
	return (j + ft_strlen(src));
}
