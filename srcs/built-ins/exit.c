/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:10:52 by tgriffit          #+#    #+#             */
/*   Updated: 2022/06/03 14:18:55 by tgriffit         ###   ########.fr       */
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


void	ft_exit(char **arg, size_t	nb_args)
{
	if (!arg || nb_args <= 1)
		exit(0);
	if (ft_check_all_args(arg, nb_args))
		exit (ft_atoi(arg[1]));
}

int	main(int argc, char **argv)
{
	ft_exit(argv, argc);
}
