/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:01:37 by tgriffit          #+#    #+#             */
/*   Updated: 2022/09/21 12:08:05 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../incs/minishell.h"

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
	while (stop[0][i] && stop[0][i] != ' ')
	{
		result[i] = stop[0][i];
		i++;
	}
	result[i] = '\0';
	ft_strlcpy(*stop, *stop + i + 1, ft_strlen(*stop));
	return (result);
}

/**
 * The arg written is set to empty if there's no command before <<
 * @param arg
 */
void	ft_write_arg_if_valid(char **arg)
{
	if (*arg[0] != '<')
		ft_strlcpy(*arg, *arg, get_next_valid_sep(*arg) - *arg);
	else
	{
		free(*arg);
		*arg = "";
	}
}

t_argmode	*replace_heredocs(t_argmode *args, size_t nb_args)
{
	size_t	i;

	i = 0;
	while (i < nb_args)
	{
		if (args[i].mode == HEREDOC)
		{
			ft_write_arg_if_valid(&args[i].arg);
			args[i + 1].arg = ft_heredoc(get_stop_word(&args[i + 1].arg));
			if (!args[i].arg)
			{
				free_t_argmode(args, nb_args);
				ft_putendl_fd("heredoc: stop word invalid. Aborted.", 2);
				return (NULL);
			}
		}
		i++;
	}
	return (args);
}
