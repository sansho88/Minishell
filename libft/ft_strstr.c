/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:18:26 by tgriffit          #+#    #+#             */
/*   Updated: 2021/08/17 18:00:03 by tgriffit         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, const char *to_find)
{
	int	i;
	int	indexfind;
	int	findlen;

	i = 0;
	findlen = 0;
	while (to_find[findlen])
		findlen++;
	if (findlen == 0)
		return (str);
	while (str[i])
	{
		indexfind = 0;
		while (str[i + indexfind] == to_find[indexfind])
		{
			++indexfind;
			if (indexfind == findlen)
				return (str + i);
		}
		i++;
	}
	return (NULL);
}
