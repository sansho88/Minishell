/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:58:58 by tgriffit          #+#    #+#             */
/*   Updated: 2022/04/19 18:05:26 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_cleansplit(char **str, int index)
{
	while (index)
	{
		free(str[index]);
		index--;
	}
	free(str);
}

static int	ft_sepscntr(char const *s, char c)
{
	int		i;
	int		count_words;

	i = 0;
	count_words = 0;
	while (s[i])
	{
		if ((s[i + 1] == c || s[i + 1] == 0) && s[i] != c)
			count_words++;
		i++;
	}
	return (count_words);
}

static void	ft_write_words(char const *s, char sep, char **res, int nbseps)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (i < nbseps)
	{
		k = 0;
		while (s[j] && s[j] == sep)
			j++;
		while (s[j] && s[j] != sep)
			res[i][k++] = s[j++];
		res[i][k] = 0;
		i++;
	}
}

static int	ft_givememspace(char const *s, char c, char **res, int nbseps)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (i < nbseps)
	{
		k = 0;
		while (s[j] && s[j] == c)
			j++;
		while (s[j] && s[j] != c)
		{
			j++;
			k++;
		}
		res[i] = (char *)malloc(sizeof(char) * (k + 1));
		if (!res[i])
		{
			ft_cleansplit(res, i);
			return (0);
		}
		i++;
	}
	return (1);
}

/**
* Alloue (avec malloc(3)) et retourne un tableau
* de chaines de caracteres obtenu en séparant ’s’ à
* l’aide du caractère ’c’, utilisé comme délimiteur.
* Le tableau doit être terminé par NULL.
* @param s = La chaine de caractères à découper.
* @param c = Le caractère délimitant.
* @return Le tableau de nouvelles chaines de caractères,
* résultant du découpage. NULL si l’allocation échoue.
*/
char	**ft_split(char const *s, char c)
{
	char	**res;
	int		nbseps;

	if (!s)
		return (0);
	nbseps = ft_sepscntr(s, c);
	res = (char **)malloc(sizeof(char *) * (nbseps + 1));
	if (!res)
		return (0);
	if (!ft_givememspace(s, c, res, nbseps))
		return (0);
	ft_write_words(s, c, res, nbseps);
	res[nbseps] = 0;
	return (res);
}
