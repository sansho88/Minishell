/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_cmdline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:13:41 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/24 11:56:17 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../incs/minishell.h"
#define ERR_IS_DIR "Conchito: /: is a directory"

bool	is_char_inquotes(const char *cmdline, const char *str_target)
{
	char	*trgt;
	char	*next_sep;
	size_t	i;

	i = 0;
	while (str_target && str_target[i])
	{
		trgt = ft_strchr(cmdline, str_target[i]);
		while (trgt)
		{
			next_sep = get_next_valid_sep(trgt + 1);
			if (!is_str_in_quotes(cmdline, trgt, next_sep, '"')
				|| !is_str_in_quotes(cmdline, trgt, next_sep, '\''))
				return (true);
			trgt = ft_strchr(trgt + 1, str_target[i]);
		}
		i++;
	}
	return (false);
}

bool	are_slashs_ok(char	*cmdline)
{
	size_t			i;
	const size_t	len = ft_strlen(cmdline);

	i = 0;
	while (i < len)
	{
		while (is_str_in_quotes(cmdline, &cmdline[i],
				get_next_valid_sep(&cmdline[i + 1]), '"'))
				i++;
		if (i < len - 1 && cmdline[i] == '/' && cmdline[i + 1] == '/')
		{
			printf("%s\n", ERR_IS_DIR);
			return (false);
		}
		i++;
	}
	return (true);
}

char	*ft_del_last_space(char *str)
{
	(void)ft_strlcpy(str, str, ft_strlen(str));
	return (str);
}
