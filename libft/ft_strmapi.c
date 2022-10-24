/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:21:37 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/24 16:11:29 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Applique la fonction ’f’ à chaque caractère de la chaine de caractères
 * passée en argument pour créer une nouvelle chaine de caractères
 * (avec malloc(3)) résultant des applications successives de ’f’.
 * @param s = La chaine de caractères sur laquelle itérer
 * @param f = La fonction à appliquer à chaque caractère.
 * @return La chaine de caractères résultant des applications successives de f.
 * Retourne NULL si l’allocation échoue.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*res;

	if (s == 0 || f == 0)
		return (0);
	res = ft_strdup(s);
	if (!res)
		return (0);
	i = 0;
	while (s[i])
	{
		res[i] = f(i, res[i]);
		i++;
	}
	return (res);
}
