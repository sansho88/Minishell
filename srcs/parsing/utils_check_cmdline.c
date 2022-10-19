/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_cmdline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:13:41 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/19 12:06:16 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../incs/minishell.h"

bool	is_char_inquotes(const char *cmdline, const char *str_target)
{
	char	*trgt;
	size_t	i;

	i = 0;
	while (str_target[i])
	{
		trgt = ft_strchr(cmdline, str_target[i]);
		while (trgt)
		{
			if (!is_str_in_quotes(cmdline, trgt, get_next_valid_sep(trgt + 1), '"'))
				return (true);
			trgt = ft_strchr(trgt + 1, str_target[i]);
		}
		i++;
	}
	return (false);
}
