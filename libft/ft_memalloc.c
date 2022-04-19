/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 20:19:03 by tgriffit          #+#    #+#             */
/*   Updated: 2021/12/17 20:40:07 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftminitalk.h"

void	*ft_memalloc(size_t size)
{
	void	*res;

	res = malloc(size);
	ft_bzero(res, size);
	return (res);
}