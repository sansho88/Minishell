/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirecs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:38:42 by tgriffit          #+#    #+#             */
/*   Updated: 2022/09/26 18:50:11 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	switch_inquotes(char c, size_t *iterator, bool *in_quotes, char *between)
{
	if (c == *between)
	{
		*in_quotes = !*in_quotes;
		(*iterator)++;
	}
	if (c == '\"' && !*in_quotes)
	{
		*between = '\"';
		*in_quotes = !*in_quotes;
		(*iterator)++;
	}
	else if (c == '\'' && !*in_quotes)
	{
		*between = '\'';
		*in_quotes = !*in_quotes;
		(*iterator)++;
	}
}

void	clean_quotes(char *arg)
{
	size_t	len_arg;
	size_t	i;
	size_t	j;
	bool	in_quotes;
	char	between;

	i = 0;
	j = 0;
	in_quotes = false;
	len_arg = ft_strlen(arg);
	while (j < len_arg)
	{
		switch_inquotes(arg[j], &j, &in_quotes, &between);
		arg[i++] = arg[j++];
	}
	arg[i] = '\0';
}

/**
 * Check if the nexts 2 chars are redirection characters, and returns the mode
 * @param cmdline = A pointer to the first char to check
 * @return The "mode" (check minishell.h)
 */
int	ft_check_redir(const char *cmdline) //todo: if redir + \0 = error (str_is_alphanum(redir + 1) ?)
{
	if (!cmdline || !*(cmdline + 1))
		return (NOT_REDIR);
	if (*cmdline == '|')
		return (PIPE);
	else if (*cmdline == '>' && *(cmdline + 1) != '>')
		return (REDIR_TO_OUT);
	else if (*cmdline == '>' && *(cmdline + 1) == '>')
		return (CONCAT_TO_OUT);
	else if (*cmdline == '<' && *(cmdline + 1) != '<')
		return (REDIR_TO_IN);
	else if (*cmdline == '<' && *(cmdline + 1) == '<')
		return (HEREDOC);
	else
		return (NOT_REDIR);
}

size_t	get_nb_seps(const char *cmdline)
{
	size_t	i;
	size_t	nb_seps;

	i = -1;
	nb_seps = 0;
	while (cmdline[++i])
	{
		nb_seps += ft_check_redir(&cmdline[i]) != 0;
		if (ft_check_redir(&cmdline[i]) == 3
			|| ft_check_redir(&cmdline[i]) == 5)
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
		if (ft_check_redir(&cmdline[i]) != 0)
		{
			res[num_part].arg = ft_strndup(&cmdline[j], i - j - 1);
			res[num_part].mode = ft_check_redir(&cmdline[i]);
			j = i + (res[num_part].mode == 3 || res[num_part].mode == 5) + 1;
			num_part++;
			i = j;
		}
	}
	if (num_part == get_nb_seps(cmdline))
		end_fill_split(res, num_part, cmdline, j);
	return (replace_heredocs(res, num_part));
}
