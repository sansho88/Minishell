/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:18:09 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/24 16:11:29 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Tests for any character for which ft_isalpha or ft_isdigit is true.
 * The value of the argument must be representable as an unsigned char
 * or the value of EOF.
 * @param c = Character to test
 * @return 1 if char is alphanumeric, else 0.
 */
int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
