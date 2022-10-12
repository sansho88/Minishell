/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:02:34 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/12 15:13:28 by tgriffit         ###   ########.fr       */
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

static bool	is_chars_orgy(char *cmdline)
{
	char	*trgt;

	if (!check_chenille_char(cmdline, '|'))
	{
		printf("[hug of pipes]");
		return (true);
	}
	trgt = ft_strchr(cmdline, '\\');
	while (trgt)
	{
		if (!is_str_in_quotes(cmdline, trgt, get_next_valid_sep(trgt + 1), '"'))
			return (true);
		trgt = ft_strchr(cmdline, '\\');
	}
	trgt = ft_strchr(cmdline, ';');
	while (trgt)
	{
		if (!is_str_in_quotes(cmdline, trgt, get_next_valid_sep(trgt + 1), '"'))
			return (true);
		trgt = ft_strchr(cmdline, ';');
	}
	return (false);
}

/**
 * Clean up the command line, checks if the quotes are correctly closed, and
 * replace dollars with their corresponding environment variables.
 * @param cmdline
 * @param env
 * @return
 */
bool	is_cmdline_ok(char **cmdline, char **env)
{
	char	*testcmd;

	testcmd = ft_strtrim(*cmdline, " ");
	if (!*testcmd)
	{
		free(testcmd);
		return (false);
	}
	free(*cmdline);
	*cmdline = testcmd;
	//free(testcmd);
	if (!are_quotes_closed(*cmdline))
		return (false);
	if (is_chars_orgy(*cmdline))
	{
		printf(ERR_SYNTAX"\n");
		return (false);
	}
	if (ft_strchr(*cmdline, '$'))
		*cmdline = replace_dollars(*cmdline, env); //LEAKS !
		//printf("%s replace_dollars leak?\n", __func__ );
	return (true);
}

/**
 * Check if all args are correctly built
 * @param args
 * @param nb_args
 * @return False if something went wrong
 */
bool	are_args_ok(t_argmode	*args, size_t	nb_args)
{
	size_t	i;

	if (args == NULL || nb_args == 0)
		return (false);
	i = 0;
	while (i < nb_args)
	{
		if (!args[i].arg)
		{
			ft_putendl_fd(ERR_SYNTAX, 2);
			free_t_argmode(args, nb_args);
			return (false);
		}
		i++;
	}
	return (true);
}
