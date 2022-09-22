/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:28:43 by tgriffit          #+#    #+#             */
/*   Updated: 2022/09/22 15:07:54 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../incs/minishell.h"

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
bool	is_str_in_quotes(char *str, const char	*start, const char	*end, char quote)
{
	size_t	nb_quotes;
	bool	in_quotes;
	size_t	i;

	nb_quotes = 0;
	i = 0;
	in_quotes = false;
	puts(start);
	while (str[i] && end != NULL && (&str[i] != end + 1))
	{
		nb_quotes += str[i] == quote;
		if (&str[i] == start + 1 && nb_quotes % 2 == 1)
		{
			in_quotes = true;
			puts("oui");
		}
		if ((nb_quotes % 2 == 0 && &str[i] == end + 1))
		{
			in_quotes = false;
			printf("non | &str[i]=%p == end = %p\n", &str[i], end);
		}
		i++;
	}
	return (in_quotes);
}

int main(void) //gcc srcs/parsing/quotes.c libft/libft.a -o quotes
{
	int offset =  6;
	char *test = "THIS \'IS A VERY \'GOOD TEST\' \"STRING\"! ";
	char *first_quote = ft_strchr(test + offset, '\'');
	char *second_quote = ft_strchr(first_quote + 1, '\'');

	printf("Is in quote: %s.\n", is_str_in_quotes(test, first_quote,
												 second_quote, '\'') ? "yes" : "no");
	printf("First quote = %s\n", first_quote);
	printf("Second quote = %s\n", second_quote);
	puts(test);
}
