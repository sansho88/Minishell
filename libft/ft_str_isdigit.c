/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdigit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:00:38 by tgriffit          #+#    #+#             */
/*   Updated: 2022/06/03 14:18:16 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

/**	Tests for a decimal digit character.*/
int	ft_str_isdigit(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '-' && !ft_isdigit(str[i + 1])) || (!ft_isdigit
				(str[i]) && str[i] != '-'))
			return (0);
		i++;
	}
	return (1);
}
