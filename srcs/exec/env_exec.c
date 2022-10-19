/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:33:32 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/19 14:56:16 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	print_env(t_args *d)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (d->env[i])
	{
		while (d->env[i][j])
		{
			if (d->env[i][j] == '=')
			{
				printf("%s\n", d->env[i]);
				break ;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	env_hub(t_argmode *args, t_args *d)
{
	d->is_built_in = true;
	if (d->append_pos != 0 || d->stdout_pos != 0
		|| args[d->acutal_arg].mode == 1)
	{
		d->is_redirect = true;
		make_fork_built_in(d, args);
		return (0);
	}
	print_env(d);
	return (0);
}
