/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isalpha.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:50:48 by tgriffit          #+#    #+#             */
/*   Updated: 2022/07/27 15:58:23 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isalpha(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (false);
		i++;
	}
	return (true);
}