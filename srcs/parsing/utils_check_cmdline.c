/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_cmdline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:13:41 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/18 21:13:41 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../incs/minishell.h"

bool	is_char_inquotes(char *cmdline, char target)
{
	char	*trgt;

	trgt = ft_strchr(cmdline, target);
	while (trgt)
	{
		if (!is_str_in_quotes(cmdline, trgt, get_next_valid_sep(trgt + 1), '"'))
			return (true);
		trgt = ft_strchr(cmdline, target);
	}
	return (false);
}