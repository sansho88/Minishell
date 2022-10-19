/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:02:34 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/19 16:12:54 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * Check if there are many "wrongs" characters in a caterpillar form
 * @param cmdline
 * @param testchar
 * @param len = how any of this char can throws a chenille chars
 * @return True if everything is okay
 */
static bool	check_chenille_char(char *cmdline, char testchar, size_t len)
{
	char		*charpos;
	size_t		count;

	charpos = ft_strchr(cmdline, testchar);
	while (charpos)
	{
		count = 0;
		while (charpos && !is_str_in_quotes(cmdline, charpos,
				get_next_valid_sep((char *)charpos + 1), '"'))
		{
			while (*charpos == ' ' && *(charpos + 1))
				charpos++;
			if (*(charpos) == testchar && count < len)
				count++;
			if (count >= len)
				return (false);
			if (*(++charpos) != testchar)
				break ;
		}
		if (charpos && charpos + 1)
			charpos = ft_strchr(charpos + 1, testchar);
	}
	return (true);
}

static bool	is_chars_orgy(char *cmdline)
{
	if (!check_chenille_char(cmdline, '|', 2))
	{
		printf("[hug of pipes]");
		return (true);
	}
	if (!check_chenille_char(cmdline, '>', 3)
		|| !check_chenille_char(cmdline, '<', 3))
		return (true);
	if (is_char_inquotes(cmdline, "\\;/!"))
		return (true);
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
	if (!are_quotes_closed(*cmdline))
		return (false);
	if (is_chars_orgy(*cmdline))
	{
		printf(ERR_SYNTAX"\n");
		return (false);
	}
	if (ft_strchr(*cmdline, '$'))
		*cmdline = replace_dollars(*cmdline, env);
	return (true);
}

/**
 * Check if all args are correctly built
 * @param args
 * @param nb_args
 * @return False if something went wrong
 */
bool	are_args_ok(t_argmode	*args, size_t *nb_args)
{
	size_t	i;

	if (args == NULL || *nb_args == 0)
		return (false);
	i = 0;
	while (i < *nb_args)
	{
		if (!args[i].arg || (!*args[i].arg && args[i].mode == PIPE) \
		|| ft_check_redir(args[i].arg, args[i].arg) \
			|| ((args[i].mode == HEREDOC) && !args[i + 1].arg)
			|| ((args[i].mode != NOT_REDIR) && args[i + 1].arg \
											&& !*args[i + 1].arg))
		{
			ft_putendl_fd(ERR_SYNTAX, 2);
			free_t_argmode(args, nb_args);
			return (false);
		}
		i++;
	}
	return (true);
}
