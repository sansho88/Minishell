/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:57:54 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/05 15:36:06 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

size_t	ft_split_count(char const *s, char c)
{
	size_t	count;
	size_t	i;
	int		in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] == c && in_word)
			in_word = 0;
		if (s[i] != c && !in_word)
		{
			count++;
			in_word = 1;
		}
		i++;
	}
	return (count);
}

size_t	ft_word_len(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	free_all(char **str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_pick_str(char	const *s, char c, char	**str_res, size_t	count)
{
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	i = 0;
	while (j < count)
	{
		k = ft_word_len(&s[i], c);
		str_res[j] = ft_substr(&s[i], 0, k);
		if (!str_res[j])
		{
			free_all(str_res);
		}
		i += k;
		while (s[i] && s[i] == c)
			i++;
		j++;
	}
	return (str_res);
}

char	**ft_split(char const *s, char c)
{
	char	**str_res;
	size_t	w;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	w = ft_split_count(s, c);
	str_res = ((char **)malloc((w + 1) * sizeof(char *)));
	if (!str_res)
		return (NULL);
	str_res[w] = 0;
	ft_pick_str(&s[i], c, str_res, w);
	return (str_res);
}
