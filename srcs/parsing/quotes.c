/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:28:43 by tgriffit          #+#    #+#             */
/*   Updated: 2022/09/27 17:39:33 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../incs/minishell.h"

void	switch_inquotes(char c, size_t *iterator, bool *in_quotes, char *between)
{
	if (c == *between)
	{
		*in_quotes = !*in_quotes;
		(*iterator)++;
	}
	else if (c == '\"' && !*in_quotes)
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
		printf("[%s]arg:%c\n", __func__ , arg[j]);
		switch_inquotes(arg[j], &j, &in_quotes, &between); //fixme: echo ""
		//if (!in_quotes && arg[j] != between)
			arg[i++] = arg[j++];
		//else
			//j++;
	}
	arg[i] = '\0';

}


size_t	get_nb_quote(char *str, char quote)
{
	size_t	nb_quotes;
	char	*next;

	next = ft_strchr(str, quote);
	nb_quotes = (next != NULL);
	while (next && (next + 1) != NULL)
	{
		next = ft_strchr(next + 1, quote);
		nb_quotes++;
	}
	return (nb_quotes);
}

/**
 *
 * @param str
 * @param start First character of the entire string or the first quote char pos
 * @param end Next quote char pos or NULL terminating string pos
 * @param quote ' or "
 * @return True if the str is betweeen 2 sames quote chars
 */
bool	is_str_in_quotes(const char *str, const char	*start, const char	*end, char quote)
{
	size_t	nb_quotes;
	bool	in_quotes;
	size_t	i;

	nb_quotes = 0;
	i = 0;
	in_quotes = false;
	while (str[i] && end != NULL && (&str[i] != end + 1))
	{
		nb_quotes += str[i] == quote;
		if (&str[i] == start + 1 && nb_quotes % 2 == 1)
			in_quotes = true;
		if ((nb_quotes % 2 == 0 && &str[i] == end + 1))
			in_quotes = false;
		i++;
	}
	return (in_quotes);
}
