/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirecs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:38:42 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/10 13:43:55 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * Check if the nexts 2 chars are redirection characters, and returns the mode
 * @param chars = A pointer to the first char to check
 * @return The "mode" (check minishell.h)
 */
static int	ft_check_redir(const char *chars, const char	*cmdline)
{
	const bool	in_quotes = (is_str_in_quotes(cmdline, chars, chars + 1, '"')
			|| is_str_in_quotes(cmdline, chars, chars + 1, '\''));

	if (!chars || !*(chars + 1))
		return (NOT_REDIR);
	if (in_quotes)
		return (NOT_REDIR);
	if (*chars == '|')
		return (PIPE);
	else if (*chars == '>' && *(chars + 1) != '>')
		return (REDIR_TO_OUT);
	else if (*chars == '>' && *(chars + 1) == '>')
		return (CONCAT_TO_OUT);
	else if (*chars == '<' && *(chars + 1) != '<')
		return (REDIR_TO_IN);
	else if (*chars == '<' && *(chars + 1) == '<')
		return (HEREDOC);
	else
		return (NOT_REDIR);
}

size_t	get_nb_seps(const char *cmdline)
{
	size_t	i;
	size_t	nb_seps;
	int		redir;

	i = -1;
	nb_seps = 0;
	while (cmdline[++i])
	{
		redir = ft_check_redir(&cmdline[i], cmdline);
		nb_seps += (redir != 0);
		if (redir == 3 || redir == 5)
			nb_seps--;
		if (i > 0 && (cmdline[i - 1] == '>' || cmdline[i - 1] == '<'))
				i++;
	}
	return (nb_seps);
}

void	ft_trim_args(t_argmode *argmode, size_t nb_args)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (i < nb_args)
	{
		tmp = ft_strdup(argmode[i].arg);
		if (argmode[i].arg && *argmode[i].arg)
			free(argmode[i].arg);
		argmode[i].arg = ft_strtrim(tmp, " ");
		if (are_quotes_closed(argmode[i].arg))
			clean_quotes(argmode[i].arg);
		free(tmp);
		i++;
	}
}

void	end_fill_split(t_argmode	*res, int num_part, char *cmdline, int j)
{
	if (res[num_part].arg != NULL && *res[num_part].arg)
		free(res[num_part].arg);
	res[num_part].arg = ft_strtrim(cmdline + j, " ");
	res[num_part].mode = 0;
	ft_trim_args(res, num_part + 1);
}

/**
 * Create the amount of t_argmode structs and
 * @param cmdline
 * @return
 */
t_argmode	*create_targmode_array(char *cmdline)
{
	int			i;
	int			j;
	int			num_part;
	t_argmode	*res;

	i = -1;
	j = 0;
	num_part = 0;
	res = ft_calloc(sizeof(t_argmode), get_nb_seps(cmdline) + 1);
	if (!res)
		return (NULL);
	while (cmdline[++i] && num_part != get_nb_seps(cmdline))
	{
		if (ft_check_redir(&cmdline[i], cmdline) != 0)
		{
			res[num_part].arg = ft_strndup(&cmdline[j], i - j);
			res[num_part].mode = ft_check_redir(&cmdline[i], cmdline);
			j = i + (res[num_part].mode == 3 || res[num_part].mode == 5) + 1;
			num_part++;
			i = j;
		}
	}
	if (num_part == get_nb_seps(cmdline))
		end_fill_split(res, num_part, cmdline, j);
	return (replace_heredocs(res, num_part));
}
