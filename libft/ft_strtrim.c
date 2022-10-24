/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:32:42 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/24 17:17:37 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_charinset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

/**
 * Alloue (avec malloc(3)) et retourne une copie de la chaine ’s1’, sans les
 * caractères spécifiés dans ’set’ au début et à la fin
 * de la chaine de caractères.
 * @param s1
 * @param set
 * @return La chaine de caractères trimmée. NULL si l’allocation échoue.
 */
char	*ft_strtrim(char const *s1, const char *set)
{
	char		*res;
	size_t		starttrim;
	size_t		endtrim;

	starttrim = 0;
	endtrim = ft_strlen(s1) - 1;
	if (!s1)
		return (0);
	if (ft_strlen(s1) < 1 || ft_strlen(set) < 1)
		return ((char *) ft_strdup(s1));
	while (ft_charinset(s1[starttrim], set) && s1[starttrim])
		starttrim++;
	while (ft_charinset(s1[endtrim], set) && endtrim > starttrim)
		endtrim--;
	res = ft_substr(s1, starttrim, endtrim - starttrim + 1);
	if (!res)
		return (malloc(1));
	return (res);
}
