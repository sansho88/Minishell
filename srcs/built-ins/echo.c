/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:20:21 by tgriffit          #+#    #+#             */
/*   Updated: 2022/05/23 18:49:16 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

bool	is_opt_valid(char *opt)
{
	size_t	i;

	i = 0;
	if (opt[i] != '-')
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
void	ft_echo(char *arg)
{
	bool	n;
	char	**split_arg;
	int		nb_args;
	int		i;

	split_arg = ft_split_len(arg, ' ', &nb_args);
	n = is_opt_valid(split_arg[0]);
	i = n - 1;
	free(arg);
	arg = NULL;
	while (++i < nb_args - 1)
	{
		arg = ft_strjoin_free(arg, split_arg[i], 1);
		if (i != nb_args - 2)
			arg = ft_strjoin_free(arg, " ", 1);
	}
	free_args(split_arg, nb_args + 1);
	if (n == false)
		ft_putendl_fd(arg, 1);
	else
		ft_putstr_fd(arg, 1);
	free(arg);
}
/*

int	main(int argc, char **argv)
{
	int i = 1;
	char *arg;
	char *final_arg;

	arg = ft_strdup("");
	if (argc < 2)
		return (0);
	while (++i < argc)
	{
		arg = ft_strjoin_free(arg, argv[i], 1);
		if (i != argc)
			arg = ft_strjoin_free(arg, " ", 1);
	}
	final_arg = ft_strtrim(arg, " ");
	free(arg);
	ft_echo(final_arg);
}
*/
