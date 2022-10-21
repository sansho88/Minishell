/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:20:21 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/21 15:31:09 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

bool	is_opt_valid(char *opt)
{
	size_t	i;

	i = 0;
	if (!opt || ft_strlen(opt) < 2)
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

size_t	get_nb_opts_ok(char **all_args, size_t nb_args)
{
	size_t	n;
	size_t	i;

	n = 0;
	i = 1;
	while (i < nb_args && (i == n + 1))
	{
		n += is_opt_valid(all_args[i++]);
		if (i > n + 1)
			break ;
	}
	return (n);
}

/**
 * Works as the bash's "echo" built-in. The -n option works even with "-nnn"\n
 *
 * @param arg
 */
void	ft_echo(char *arg, t_args *d)
{
	size_t		n;
	char		**split_arg;
	int			nb_args;
	char		*msg;

	d->is_built_in = true;
	split_arg = ft_split_len(arg, ' ', &nb_args);
	n = get_nb_opts_ok(split_arg, nb_args);
	msg = ft_strstr(arg, split_arg[n + 1]);
	msg = clean_quotes(msg);
	if (n == 0)
		printf("%s\n", msg);
	else
		printf("%s", msg);
	free_args(split_arg, nb_args + 1);
}

int	echo_hub(char *arg, t_args *d, t_argmode *args)
{
	d->is_built_in = true;
	if (d->append_pos != 0 || d->stdout_pos != 0 || \
	args[d->acutal_arg].mode == 1)
	{
		d->is_redirect = true;
		make_fork_built_in(d, args);
		return (0);
	}
	ft_echo(arg, d);
	return (0);
}
