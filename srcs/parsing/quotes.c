/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:28:43 by tgriffit          #+#    #+#             */
/*   Updated: 2022/09/21 18:31:13 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../incs/minishell.h"

/**
 *
 * @param str
 * @param start First character of the entire string or the first quote char pos
 * @param end Next quote char pos or NULL terminating string pos
 * @param quote ' or "
 * @return True if the str is betweeen 2 sames quote chars
 */
bool	is_str_in_quotes(char *str, char	*start, char	*end, char quote) //fixme
{
	size_t	nb_quotes;
	bool	in_quotes;
	size_t	i;

	nb_quotes = 0;
	i = 0;
	in_quotes = false;
	while (str[i])
	{
		nb_quotes += str[i] == quote;
		if (&str[i] == start && nb_quotes % 2 == 1)
		{
			in_quotes = true;
			puts("oui");
		}
		if (nb_quotes % 2 == 0 && &str[i] == end)
		{
			in_quotes = false;
			printf("non | &str[i]=%p == end = %p\n", &str[i], end);
		}
		i++;
	}
	return (in_quotes);
}

int main(void)
{
	char *test = "THIS \'IS A VERY GOOD A TEST \"STRING\"! ";
	char *first_quote = ft_strchr(test, '\'');
	char *second_quote = ft_strchr(first_quote, '\'');

	printf("Is in quote: %d\n", is_str_in_quotes(test, first_quote,
												 second_quote, '\''));
	puts(test);
}
