/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:05:27 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/24 18:44:57 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** Writes len bytes of
 * value c (converted to an unsigned char) to the string str.
 * @returns Its first argument.*/

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned int	i;
	char			*res;

	i = 0;
	res = str;
	while (i < len)
		res[i++] = (unsigned char)c;
	return (res);
}
