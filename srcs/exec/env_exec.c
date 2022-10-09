/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:33:32 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/08 19:04:40 by rgeral           ###   ########.fr       */
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
	print_env(d);
	return (0);
}
