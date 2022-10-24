/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:52:37 by tgriffit          #+#    #+#             */
/*   Updated: 2022/05/13 11:37:33 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Writes n zeroed bytes to the string s. If n is zero, ft_bzero() does nothing.
 * @param s = Pointer to nullify
 * @param n = Amount of null bytes to include
 */
void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*res;

	res = s;
	i = 0;
	while (i < n)
		res[i++] = 0;
}
