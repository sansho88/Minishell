/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirecs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:38:42 by tgriffit          #+#    #+#             */
/*   Updated: 2022/05/10 16:37:12 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

size_t	ft_cnt_redirecs(const char *line)
{
	size_t		count;
	size_t		i;
	bool		is_in_quotes;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			is_in_quotes = !is_in_quotes;
		if (is_in_quotes == false)
		{
			if (line[i] == '>' && line[i + 1] && line[i + 1] != '>')
				count++;
			else if (line[i] == '<' && line[i + 1] && line[i + 1] != '<')
				count++;
		}
		i++;
	}
	return (count);
}

/**
 * Check if the nexts 2 chars are redirection characters, and returns the mode
 * @param cmdline = A pointer to the first char to check
 * @return The "mode" (check minishell.h)
 */
int	ft_check_redir(const char *cmdline)
{
	if (!cmdline)
		return (NOT_REDIR);
	if (*cmdline == '|' && *(cmdline + 1))
		return (PIPE);
	else if (*cmdline == '>' && *(cmdline + 1) && *(cmdline + 1) != '>')
		return (REDIR_TO_OUT);
	else if (*cmdline == '>' && *(cmdline + 1) && *(cmdline + 1) == '>')
		return (CONCAT_TO_OUT);
	else if (*cmdline == '<' && *(cmdline + 1) && *(cmdline + 1) != '<')
		return (REDIR_TO_IN);
	else if (*cmdline == '<' && *(cmdline + 1) && *(cmdline + 1) == '<')
		return (CONCAT_TO_IN);
	else
		return (NOT_REDIR);
}

t_argmode	ft_fill_argmode_array(char *cmdline, size_t i, int argc)
{
	char		**tmp_split;
	int			tmp_splitlen;
	t_argmode	argmode_array;

	tmp_split = ft_split_len(cmdline, *(cmdline + i), &tmp_splitlen);
	argmode_array.arg = ft_strtrim(tmp_split[argc], " ");
	argmode_array.mode = ft_check_redir(cmdline + i);
	//dprintf(1, "[%s]argmode_array.arg = %s_|_ argmode_array.mode = %d\n",__func__, argmode_array.arg, argmode_array.mode);
	while (tmp_splitlen > 0)
		//free(tmp_split[tmp_splitlen--]);
	//free(tmp_split);
	return (argmode_array);
}

/**
 * Take all the args and checks if each couple of chars is a redirect.
 *
 * @param cmdline = The cmdline sent by the user.
 * @param argc = Will takes the value of numbers of args between each redirect.
 * @return A t_argmode struct which contains each arg and the "mode" associated
 * (check minishell.h)
 */
t_argmode	*split_arg_redirect(char *cmdline, int *argc)
{
	t_argmode	*res;
	size_t		i;

	res = malloc(ft_cnt_redirecs(cmdline) * sizeof(t_argmode *));
	i = 0;
	*argc = 0;
	while (cmdline[i])
	{
		if (ft_check_redir(cmdline + i) != 0)
		{
			res[*argc] = ft_fill_argmode_array(cmdline, i, *argc);
			//dprintf(1, "res[%d] = %s\n", *argc, res[*argc].arg);
			(*argc)++;
		}
		else if (!ft_strchr(cmdline + i, '>') && !ft_strchr(cmdline + i, '<')
			&& !ft_strchr(cmdline + i, '|'))
		{
			res[*argc].arg = ft_strtrim(cmdline + i, " ");
			res[*argc].mode = 0;
			(*argc)++;
			return (res);
		}
		i++;
	}
	return (res);
}
