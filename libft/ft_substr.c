/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:46:59 by tgriffit          #+#    #+#             */
/*   Updated: 2022/04/19 18:01:28 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Alloue (avec malloc(3)) et retourne une chaine de caractères issue de la
 * chaine ’s’. Cette nouvelle chaine commence à l’index ’start’ et
 * a pour taille maximale ’len’.
 * @param s = La chaine de laquelle extraire la nouvelle chaine
 * @param start = L’index de début de la nouvelle chaine dans la chaine ’s’.
 * @param len = La taille maximale de la nouvelle chaine.
 * @return La nouvelle chaine de caractere. NULL si l’allocation échoue.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	while (i < len && s[start + i] != '\0')
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
