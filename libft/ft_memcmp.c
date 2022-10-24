/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:45:21 by tgriffit          #+#    #+#             */
/*   Updated: 2022/05/13 11:37:33 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Compares byte string s1 against byte string s2.
 * Both strings are assumed to be n bytes long.
 *
 * @return Returns zero if the two strings are identical, otherwise returns the
 * difference between the first two differing bytes (treated as unsigned char
 * values, so that `\200' is greater than `\0', for example).
 * Zero-length strings are always identical.  This behavior is not required
 * by C and portable code should only depend on the sign of the returned value.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n - 1 && str1[i] == str2[i])
		i++;
	return (((unsigned char)str1[i] - (unsigned char)str2[i]));
}
