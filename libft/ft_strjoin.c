/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:24:51 by tgriffit          #+#    #+#             */
/*   Updated: 2021/11/04 17:23:13 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/**
 * Alloue (avec malloc(3)) et retourne une nouvelle chaine, résultat de la
 * concaténation de s1 et s2.
 * @param s1
 * @param s2
 * @return La nouvelle chaine de caractères. NULL si l’allocation échoue.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1size;
	size_t	s2size;

	if (!s1 || !s2)
		return (0);
	s1size = ft_strlen(s1);
	s2size = ft_strlen(s2);
	res = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (res)
	{
		ft_memcpy(res, s1, s1size);
		ft_memcpy(res + s1size, s2, s2size + 1);
	}
	return (res);
}
