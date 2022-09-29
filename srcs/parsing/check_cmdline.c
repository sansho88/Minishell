/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:02:34 by tgriffit          #+#    #+#             */
/*   Updated: 2022/09/28 19:14:46 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * Check if there are many "wrongs" characters in a caterpillar form
 * @param cmdline
 * @param testchar
 * @return True if everything is okay
 */
static bool	check_chenille_char(char *cmdline, char testchar)
{
	char	*charpos;

	charpos = ft_strchr(cmdline, testchar);
	if (charpos)
	{
		if (!is_str_in_quotes(cmdline, charpos, get_next_valid_sep(charpos + 1),
				'"') && *(charpos + 1) == testchar)
			return (false);
	}
	return (true);
}

static bool	is_chars_partouze(char *cmdline)
{
	char	*target;

	if (!check_chenille_char(cmdline, '|'))
	{
		puts("chars chenille");
		return (true);
	}
	target = ft_strchr(cmdline, '\\');
	while (target)
	{
		if (!is_str_in_quotes(cmdline, target, get_next_valid_sep(target + 1), '"'))
			return (true);
		target = ft_strchr(cmdline, '\\');
	}
	target = ft_strchr(cmdline, ';');
	while (target)
	{
		if (!is_str_in_quotes(cmdline, target, get_next_valid_sep(target + 1), '"'))
			return (true);
		target = ft_strchr(cmdline, ';');
	}
	return (false);
}

bool	is_cmdline_ok(char **cmdline, char **env)
{
	char	*testcmd;

	testcmd = ft_strtrim(*cmdline, " ");
	if (!*testcmd)
	{
		free(testcmd);
		return (false);
	}
	if (!are_quotes_closed(*cmdline))
		return (false);
	if (is_chars_partouze(*cmdline))
	{
		printf("Chars partouze\n");
		return (false);
	}
	if (ft_strchr(*cmdline, '$'))
		*cmdline = replace_dollars(*cmdline, env);
	return (true);
}

static bool	str_contains_redir(char *str) //fixme
{
	char	*target;
	char	*end_target;

	target = ft_strchr(str, '>');
	while (target)
	{
		end_target = get_next_valid_sep(target);
		if (!is_str_in_quotes(str, target, end_target, '"'))
			return (true);
		target = ft_strchr(str, '>');
	}
	target = ft_strchr(str, '<');
	while (target)
	{
		end_target = get_next_valid_sep(target);
		if (!is_str_in_quotes(str, target, end_target, '"'))
			return (true);
		target = ft_strchr(str, '<');
	}
	target = ft_strchr(str, '|');
	while (target)
	{
		end_target = get_next_valid_sep(target);
		if (!is_str_in_quotes(str, target, end_target, '"'))
			return (true);
		target = ft_strchr(str, '|');
	}
	return (false);
	//todo: a function, maybe "get_target_redir", for norm
	//todo later: perform the same check when the next true redir is found
}

bool	are_args_ok(t_argmode	*args, size_t	nb_args)
{
	size_t	i;

	if (args == NULL || nb_args == 0)
		return (false);
	i = 0;
	while (i < nb_args)
	{
		if (!args[i].arg || (!ft_str_isalnum(args[i].arg)
				&& str_contains_redir(args[i].arg)))
		{
			ft_putendl_fd("Conchito: syntax error", 2);
			free_t_argmode(args, nb_args);
			return (false);
		}
		i++;
	}
	return (true);
}
