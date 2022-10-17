/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:28:43 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/17 11:52:02 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	switch_inquotes(char c, size_t *i, bool *in_quotes, char *between)
{
	if (c == *between)
	{
		*in_quotes = !*in_quotes;
		(*i)++;
	}
	else if (c == '\"' && !*in_quotes)
	{
		*between = '\"';
		*in_quotes = !*in_quotes;
		(*i)++;
	}
	else if (c == '\'' && !*in_quotes)
	{
		*between = '\'';
		*in_quotes = !*in_quotes;
		(*i)++;
	}
}

void	clean_quotes(char *arg)
{
	const size_t	len_arg = ft_strlen(arg);
	size_t			i;
	size_t			j;
	bool			in_quotes;
	char			between;

	i = 0;
	j = 0;
	in_quotes = false;
	while (j < len_arg)
	{
		switch_inquotes(arg[j], &j, &in_quotes, &between);
		j += (j > 0 && arg[j - 1] == between && arg[j] == between);
		arg[i++] = arg[j++];
	}
	arg[i] = '\0';
}

bool	are_quotes_closed(const char *cmdline)
{
	size_t	nb_single_quotes;
	size_t	nb_double_quotes;
	size_t	i;

	nb_single_quotes = 0;
	nb_double_quotes = 0;
	i = 0;
	while (cmdline[i])
	{
		if (cmdline[i] == '"' && nb_single_quotes % 2 == 0)
			nb_double_quotes++;
		else if (cmdline[i] == '\'' && nb_double_quotes % 2 == 0)
			nb_single_quotes++;
		i++;
	}
	if (nb_double_quotes % 2 == 1)
		ft_putendl_fd("Double-Quotes not closed", 2);
	if (nb_single_quotes % 2 == 1)
		ft_putendl_fd("Single-Quotes not closed", 2);
	return (nb_single_quotes % 2 == 0 && nb_double_quotes % 2 == 0);
}

bool	is_envar_in_sngl_quotes(const char *str, size_t lenstr, bool is_env_var)
{
	if (!(str - is_env_var) || *(str - is_env_var) != '\'')
		return (false);
	return (str[lenstr] + 1 && str[lenstr] + 1 == '\'');
}

/**
 *
 * @param str
 * @param start First character of the entire string or the first quote char pos
 * @param end Next quote char pos or NULL terminating string pos
 * @param quote ' or "
 * @return True if the str is betweeen 2 sames quote chars
 */
bool	is_str_in_quotes(const char *str, const char *start, const char *end, \
						char quote)
{
	size_t	nb_quotes;
	bool	in_quotes;
	size_t	i;

	nb_quotes = 0;
	i = 0;
	in_quotes = false;
	while (str[i] && end != NULL && (&str[i] != end))
	{
		nb_quotes += str[i] == quote;
		if (&str[i] == start && nb_quotes % 2 == 1)
			in_quotes = true;
		if ((nb_quotes % 2 == 0 && &str[i] == end + 1))
			in_quotes = false;
		i++;
	}
	return (in_quotes);
}
