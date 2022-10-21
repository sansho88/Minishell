/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:01:37 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/21 15:30:59 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * Get only the word which stop the heredoc, and remove it from the t_argmode
 * for keep only what is next after the heredoc. \n
 * Example: << stop cat > file == /heredoc.txt > file
 * @param stop
 * @return
 */
char	*get_stop_word(char **stop)
{
	size_t	i;
	char	*result;

	i = 0;
	if (!stop || !*stop || !**stop)
		return (NULL);
	result = ft_strdup(*stop);
	if (!is_str_in_quotes(*stop, *stop, *stop + ft_strlen(*stop), '"') \
	&& !is_str_in_quotes(*stop, *stop, *stop + ft_strlen(*stop), '\''))
	{
		while (stop[0][i] && stop[0][i] != ' ')
		{
			result[i] = stop[0][i];
			i++;
		}
		result[i] = '\0';
	}
	result = clean_quotes(result);
	ft_strlcpy(*stop, *stop + i + 1, ft_strlen(*stop));
	return (result);
}

t_argmode	*replace_heredocs(t_argmode *args, size_t nb_args)
{
	size_t	i;
	char	*stop;

	i = 0;
	while (i < nb_args)
	{
		if (args[i].mode == HEREDOC)
		{
			if (args[i].arg[0] != '<')
				ft_strlcpy(args[i].arg, args[i].arg, \
					get_next_valid_sep(args[i].arg) - args[i].arg + 1);
			stop = get_stop_word(&args[i + 1].arg);
			free(args[i + 1].arg);
			args[i + 1].arg = ft_heredoc(stop);
			free(stop);
		}
		i++;
	}
	return (args);
}
