/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirecs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:38:42 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/25 21:38:26 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * Check if the nexts 2 chars are redirection characters, and returns the mode
 * @param chars = A pointer to the first char to check
 * @return The "mode" (check minishell.h)
 */
int	ft_check_redir(const char *chars, const char	*cmdline)
{
	const bool	in_quotes = (is_str_in_quotes(cmdline, chars, chars + 1, '"')
			|| is_str_in_quotes(cmdline, chars, chars + 1, '\''));

	if (!chars || in_quotes)
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

char	*create_first_targmode(char **args)
{
	char		*base;
	int			redir;
	size_t		i;

	i = 0;
	base = ft_strdup("");
	while (base && args && args[i])
	{
		redir = ft_check_redir(args[i], *args);
		if (redir == PIPE)
			break ;
		if (redir >= REDIR_TO_OUT && redir <= HEREDOC)
			i++;
		else
		{
			base = ft_strjoin_free(base, args[i], 1);
			if (base)
				base = ft_strjoin_free(base, " ", 1);
			if (!base)
				break ;
		}
		if (++i > 1 && !args[i - 1])
			break ;
	}
	return (ft_del_last_space(base));
}

void	fill_targmode_array(t_argmode *res, char **args)
{
	size_t	i;
	int		j;
	int		mode;

	i = 0;
	j = 0;
	while (args && args[i])
	{
		mode = ft_check_redir(args[i], *args);
		if (i == 0 || mode == PIPE)
		{
			free(res[j + (mode == PIPE)].arg);
			res[j + (mode == PIPE)].arg = create_first_targmode(
					args + i + (mode == PIPE));
		}
		if (mode >= PIPE && mode <= HEREDOC)
		{
			res[j].mode = mode;
			if (mode != PIPE && args[i + 1])
				res[j + 1].arg = ft_strdup(args[++i]);
			res[j + 1].mode = 0;
			++j;
		}
		++i;
	}
}

void	free_array(char **args)
{
	int	i;

	if (args)
	{
		i = 0;
		while (args[i])
			free(args[i++]);
		free(args);
	}
}

/**
 * Create the amount of t_argmode structs and
 * @param cmdline
 * @return
 */
t_argmode	*create_targmode_array(char *cmdline, char **env)
{
	t_argmode	*res;
	char		**args;
	int			nb_seps;

	res = NULL;
	args = ft_split_quotes(cmdline);
	if (!args)
		return (NULL);
	nb_seps = get_nb_seps(args);
	res = ft_calloc(nb_seps + 2, sizeof(t_argmode));
	if (!res)
		return (NULL);
	fill_targmode_array(res, args);
	free_array(args);
	return (replace_heredocs(res, nb_seps + 1, env));
}
