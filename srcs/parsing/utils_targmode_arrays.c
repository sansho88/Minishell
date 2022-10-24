/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_targmode_arrays.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:18:04 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/24 18:02:18 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../incs/minishell.h"

int	convert_quote_mode(int quote_mode, char quote)
{
	if (quote == '\'' && quote_mode != 2)
		quote_mode = 1 - quote_mode;
	else if (quote == '"' && quote_mode != 1)
		quote_mode = 2 - quote_mode;
	return (quote_mode);
}

int	wordlen(const char *line)
{
	int	quote_mode;
	int	i;
	int	redir;

	quote_mode = 0;
	i = -1;
	while (line && line[++i] && (quote_mode != 0 || !ft_is_space(line[i])))
	{
		quote_mode = convert_quote_mode(quote_mode, line[i]);
		redir = ft_check_redir(line + i, line);
		if (redir >= REDIR_TO_OUT && redir <= HEREDOC)
		{
			if (i == 0)
				return ((redir == HEREDOC || redir == CONCAT_TO_OUT) + 1);
			break ;
		}
		if (redir == PIPE)
		{
			if (i == 0)
				return (PIPE);
			break ;
		}
	}
	return (i);
}

int	count_words(const char *line)
{
	int	nwords;

	nwords = 0;
	while (*line)
	{
		while (ft_is_space(*line))
			++line;
		if (*line)
		{
			++nwords;
			line += wordlen(line);
		}
	}
	return (nwords);
}

char	**ft_split_quotes(const char *line)
{
	char	**args;
	int		nwords;
	int		i;
	int		len;

	nwords = count_words(line);
	args = ft_calloc(sizeof(char *), nwords + 1);
	i = 0;
	while (args && i < nwords)
	{
		while (ft_is_space(*line))
			++line;
		len = wordlen(line);
		args[i] = ft_strndup(line, len);
		line += len;
		++i;
		args[i] = NULL;
	}
	return (args);
}

int	get_nb_seps(char **args)
{
	int	i;
	int	nb;
	int	redir;

	i = 0;
	nb = 0;
	while (args && args[i])
	{
		redir = ft_check_redir(args[i], *args);
		nb += (redir != 0);
		++i;
	}
	return (nb);
}
