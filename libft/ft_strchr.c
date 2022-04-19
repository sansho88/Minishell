/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:58:20 by tgriffit          #+#    #+#             */
/*   Updated: 2022/04/19 18:05:26 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 *  Locates the first occurrence of c (converted to a char) in the string
 *  pointed to by s.  The terminating null character is considered to be part
 *  of the string;
 *  therefore if c is `\0', the functions locate the terminating `\0'.
 *
 * @return a pointer to the located character, or NULL if the character does not
 * appear in the string.
 */
char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (c == 0)
		return ((char *)s + ft_strlen(s));
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}
