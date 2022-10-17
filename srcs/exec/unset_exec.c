/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:53:01 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/17 13:53:42 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	unset_exec(t_args	*d, int	j, char	**env_copy)
{
	d->env_len--;
	free(d->env[j]);
	free(env_copy[j]);
	j++;
	return(j);
}

char	**ft_env_copy(t_args *d, char *arg)
{
	char	**env_copy;
	int	i;
	int	j;

	i = 0;
	j = 0;
	env_copy = ft_calloc(d->env_len + 2, sizeof(char *));
	while (j < d->env_len + 1)
	{
		if (ft_strncmp(d->env[j], d->needle, ft_strlen(d->needle)) == 0)
			j = unset_exec(d, j, env_copy);
		else if (ft_strncmp(d->env[j], arg, ft_strlen(arg)) == 0 && !d->env[j][ft_strlen(arg)])
			j = unset_exec(d, j, env_copy);
		else
		{
			env_copy[i] = d->env[j];
			i++;
			j++;
		}
	}
	free(d->env);
	free(d->needle);
	return (env_copy);
}

int	check_if_set(t_argmode	*args, t_args	*d, char	*arg)
{
	int	i;

	i = 0;
	//if (d->needle)
	//	free(d->needle);
	d->needle = ft_strjoin(arg, "=");
	while (d->env[i])
	{
		if (ft_strncmp(d->env[i], d->needle, ft_strlen(d->needle)) == 0)
			d->env = ft_env_copy(d, arg);
		else if (ft_strncmp(d->env[i], arg, ft_strlen(arg)) == 0 && !d->env[i][ft_strlen(arg)])
			d->env = ft_env_copy(d, arg);
		i++;
	}
	return (0);
}

int	unset_hub(t_argmode *args, t_args *d)
{
	char	**arg;
	int		i;

	d->is_built_in = true;
	i = 1;
	arg = ft_split(args->arg, ' ');
	while (arg[i])
	{
		check_if_set(args, d, arg[i]);
		i++;
	}
	free_all(arg);
	return (0);
}
