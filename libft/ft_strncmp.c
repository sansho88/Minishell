/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:40:43 by tgriffit          #+#    #+#             */
/*   Updated: 2022/04/19 18:05:26 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Lexicographically compare the null-terminated strings s1 and s2, but not more
 * than n characters neither after '\0' (doesn't compare binary datas).
 *
 * @param n  = Max number of chars to compare.
 * @return An integer greater than, equal to, or less than 0, according as the
 * string s1 is greater than, equal to, or less than the string s2.
 * The comparison is done using unsigned characters, so that `\200' is greater
 * than `\0'.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n < 1)
		return (0);
	i = 0;
	if (n == 1)
		return (((unsigned char)s1[0] - (unsigned char)s2[0]));
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return (((unsigned char)s1[i] - (unsigned char)s2[i]));
}
