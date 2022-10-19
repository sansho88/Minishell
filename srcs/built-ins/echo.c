/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:20:21 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/18 11:23:38 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

bool	is_opt_valid(char *opt)
{
	size_t	i;

	i = 0;
	if (!opt || opt[i] != '-')
		return (false);
	while (opt[++i])
		if (opt[i] != 'n')
			return (false);
	return (true);
}

static void	free_args(char **args, size_t nb_args)
{
	size_t	i;

	i = 0;
	while (i < nb_args)
		free(args[i++]);
	free(args);
}

/**
 * Works as the bash's "echo" built-in. The -n option works even with "-nnn"\n
 *
 * @param arg
 */
void	ft_echo(char *arg, t_args *d)
{
	bool	n;
	char	**split_arg;
	int		nb_args;
	int		i;
	char	*result;

	d->is_built_in = true;
	split_arg = ft_split_len(arg, ' ', &nb_args);
	result = ft_strdup("");
	n = is_opt_valid(split_arg[1]);
	i = n;
	while (++i < nb_args)
	{
		result = ft_strjoin_free(result, split_arg[i], 1);
		if (i != nb_args - 1)
			result = ft_strjoin_free(result, " ", 1);
	}
	free_args(split_arg, nb_args + 1);
	if (n == false)
		printf("%s\n", result);
	else
		printf("%s", result);
	free(result);
}

int	echo_hub(char *arg, t_args *d, t_argmode *args)
{
	d->is_built_in = true;
	if (d->append_pos != 0 || d->stdout_pos != 0 || args[d->acutal_arg].mode == 1)
	{
		d->is_redirect = true;
		make_fork_built_in(d, args);
		return (0);
	}
	ft_echo(arg, d);
	return (0);
}
