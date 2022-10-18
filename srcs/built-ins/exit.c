/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:10:52 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/18 22:21:35 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static bool	ft_check_all_args(char **args, size_t nb_args)
{
	char	*arg_trimmed;
	size_t	i;

	i = 1;
	while (i < nb_args)
	{
		arg_trimmed = ft_strtrim(args[i++], " ");
		if (ft_strchr(arg_trimmed, ' ') != NULL || nb_args > 2)
		{
			printf("[Exit] -> Too many args\n");
			return (false);
		}
		if (!ft_str_isdigit(arg_trimmed))
		{
			printf("[Exit]: %s -> numeric argument required", arg_trimmed);
			exit (-1);
		}
		free(arg_trimmed);
	}
	return (true);
}


void	ft_exit(t_args *d, t_argmode *argv)
{
	int		nb_args;
	char	**args;

	d->is_built_in = true;
	args = ft_split_len(argv->arg, ' ', &nb_args);
	while (args[nb_args])
		nb_args++;
	if (!args || nb_args <= 1)
		exit(0);
	if (ft_check_all_args(args, nb_args))
	{
		exit (ft_atoi(args[1]) % 256);
	}
}

int	exit_hub(t_args *d, t_argmode *argv)
{
	d->is_built_in = true;
	if (argv[d->acutal_arg].mode == 1)
	{
		d->is_redirect = true;
		make_fork_built_in(d, argv);
		return (0);
	}
	ft_exit(d, argv);
	return (0);
}
