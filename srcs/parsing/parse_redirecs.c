/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirecs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:38:42 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/20 21:07:38 by tgriffit         ###   ########.fr       */
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

size_t	get_nb_seps(const char *cmdline)
{
	size_t			i;
	size_t			nb_seps;
	int				redir;
	const size_t	len = ft_strlen(cmdline);

	i = 0;
	nb_seps = 0;
	while (cmdline[i])
	{
		redir = ft_check_redir(&cmdline[i], cmdline);
		nb_seps += (redir != 0 && !(redir == 3 || redir == 5));
		i += (i > 0 && i + 2 < len
				&& (cmdline[i - 1] == '>' || cmdline[i - 1] == '<')) + 1;
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
		if (argmode[i].arg)
			free(argmode[i].arg);
		argmode[i].arg = ft_strtrim(tmp, " ");
		if (are_quotes_closed(argmode[i].arg))
		{
			argmode[i].pure_arg = ft_strdup(argmode[i].arg);
			clean_quotes(argmode[i].arg);
		}
		free(tmp);
		i++;
	}
}

void	end_fill_split(t_argmode	*res, int num_part, char *cmdline, int j)
{
	if (res[num_part].arg != NULL)
		free(res[num_part].arg);
	printf("[%s]args[i].arg=%s\n", __func__, res[num_part].arg);
	res[num_part].arg = ft_strtrim(cmdline + j, " ");
	res[num_part].mode = 0;
	ft_trim_args(res, num_part + 1);
}


typedef int(*t_issep)(int);

int	wordlen(const char *line, t_issep issep)
{
	int strmode;
	int len;
	int redir;

	strmode = 0;
	len = 0;
	while (line[len] && (strmode != 0 || !issep(line[len])))
	{
		if (line[len] == '\'' && strmode != 2)
			strmode = 1 - strmode;
		else if (line[len] == '"' && strmode != 1)
			strmode = 2 - strmode;
		redir = ft_check_redir(line + len, line);
		if (redir >= 2 && redir <= 5)
		{
			if (len == 0)
				return ((redir == HEREDOC || redir == CONCAT_TO_OUT) + 1);
			break;
		}
		++len;
	}
	return (len);
}

int	count_words(const char *line, t_issep issep)
{
	int	nwords;

	nwords = 0;
	while (*line)
	{
		while (issep(*line))
			++line;
		if (*line)
		{
			++nwords;
			line += wordlen(line, issep);
		}
	}
	return (nwords);
}

char	**ft_split_quotes(const char *line, t_issep issep)
{
	char **args;
	int nwords;
	int i;
	int len;

	nwords = count_words(line, issep);
	args = ft_calloc(sizeof(char *), nwords + 1);
	i = 0;
	while (i < nwords)
	{
		while (issep(*line))
			++line;
		len = wordlen(line, issep);
		args[i] = ft_strndup(line, len);
		line += len;
		++i;
	}
	args[i] = NULL;
	return (args);
}

#include <ctype.h>
#define ft_isspace isspace
/*
 * echo "bonjour "    > cactus >lol >"Hello World".txt doubida chamalo
 */

int nb_seps_lui(char **args)
{
	int	i;
	int	nb;
	int redir;

	i = 0;
	nb = 0;
	while (args[i])
	{
		redir = ft_check_redir(args[i], args[i]);
		nb += (redir != 0);
		++i;
	}
	return (nb);
}

void populate_targmode_array(t_argmode *res, char **args)
{
	int i;
	int j;
	int mode;

	i = 0;
	j = 0;
	while (args[i])
	{
		mode = ft_check_redir(args[i], args[i]);
		if (mode >= 2 && mode <= 5)
		{
			res[j].mode = mode;
			res[j + 1].arg = ft_strdup(args[++i]);
			res[j + 1].mode = 0;
			++j;
		}
		++i;
	}
}

char *create_targmode_0(char **args)
{
	char	*base;
	int redir;
	int	i;

	i = 0;
	base = ft_strdup("");
	while (args[i])
	{
		redir = ft_check_redir(args[i], args[i]);
		if (redir >= 2 && redir <= 5)
		{
			++i;
		}
		else
		{
			base = ft_strjoin_free(base, args[i], 1);
			if (base)
				base = ft_strjoin_free(base, " ", 1);
			if (!base)
				break ;
		}
		++i;
	}
	return (base);
}

void free_array(char **args)
{
	int i;

	if (args)
	{
		i = 0;
		while (args[i])
			free(args[i++]);
	}
	free(args);
}

t_argmode *create_targmode_array(char *cmdline)
{
	t_argmode	*res;
	char		**args;
	int			nb;

	res = NULL;
	args = ft_split_quotes(cmdline, ft_isspace);
	nb = nb_seps_lui(args);
	res = ft_calloc(nb + 2, sizeof(t_argmode));
	res[0].arg = create_targmode_0(args);
	populate_targmode_array(res, args);
	free_array(args);
	return (replace_heredocs(res, nb + 1));
}

/**
 * Create the amount of t_argmode structs and
 * @param cmdline
 * @return
 */
t_argmode	*create_targmode_array_pas_lui(char *cmdline)
{
	int			i;
	int			j;
	size_t		num_part;
	t_argmode	*res;

	i = -1;
	j = 0;
	num_part = 0;
	res = ft_calloc(sizeof(t_argmode), get_nb_seps(cmdline) + 1);
	if (!res)
		return (NULL);
	while (++i < (int)ft_strlen(cmdline) && num_part != get_nb_seps(cmdline))
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
		end_fill_split(res, (int)num_part, cmdline, j);
	return (replace_heredocs(res, num_part));
}
