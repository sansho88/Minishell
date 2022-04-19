/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:31:09 by tgriffit          #+#    #+#             */
/*   Updated: 2021/11/04 14:32:31 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** Tests for any printing character, including space (' ').
 *	The value of the argument must be representable as an unsigned char
 *	or the value of EOF. */
int	ft_isprint(int c)
{
	if (c < ' ' || c >= 127)
		return (0);
	return (1);
}
