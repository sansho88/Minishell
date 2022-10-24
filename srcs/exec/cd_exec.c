/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:58:14 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/24 18:35:58 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	bwd_to_directory(t_args *d, char **arg)
{
	set_old_path(d);
	if (chdir(arg[1]) == -1)
	{
		printf("bcw not fond\n");
		return (1);
	}
	return (0);
}

int	fwd_to_directory(t_args *d, char **arg)
{
	if (chdir(arg[1]) == -1)
	{
		printf("cd: no such file or directory: %s\n", arg[1]);
		return (1);
	}
	else
		set_old_path(d);
	return (0);
}

int	direct_path(char	**arg)
{
	if (chdir(arg[1]) == -1)
	{
		printf("cd: no such file or directory: %s\n", arg[1]);
		return (1);
	}
	return (0);
}

int	cd_hub(t_argmode *args, t_args *d)
{
	char	**arg;
	int		args_nbr;

	d->is_built_in = true;
	arg = ft_split(args->arg, ' ');
	if (!arg)
		return (0);
	args_nbr = cd_args_count(arg);
	if (args_nbr == 2 && ft_strncmp("/", arg[1], 1) == 0)
		direct_path(arg);
	else if (args_nbr == 2 && ft_strncmp("..", arg[1], 3) != 0)
		fwd_to_directory(d, arg);
	else if (args_nbr == 2 && ft_strncmp("..", arg[1], 3) == 0)
		bwd_to_directory(d, arg);
	free_all(arg);
	return (0);
}
