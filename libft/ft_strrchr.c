/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:30:28 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/24 18:44:57 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The strchr() function locates the first occurrence of c (converted to a char)
 * in the string pointed to by s. \n The terminating null character is considered
 * to be part of the string; therefore if c is `\0',
 * the functions locate the terminating `\0'.\n
 * The strrchr() function is identical to strchr(), except it locates the last
 * occurrence of c.
 * @param s = The String
 * @param c = The target char
 * @return  A pointer to the located character, or NULL if the character does
 * not appear in the string.
 */
char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if ((char)c == 0)
		return ((char *)s + i);
	while (i > 0)
	{
		i--;
		if (s[i] == (char)c)
			return ((char *)s + i);
	}
	return (0);
}
