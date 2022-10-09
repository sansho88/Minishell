/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:53:01 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/09 14:01:12 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**ft_env_copy(t_args *d, int i, int j, char *arg)
{
	char	**env_copy;

	env_copy = ft_calloc(d->env_len + 2, sizeof(char **));
	while (d->env[j])
	{
		if (ft_strncmp(d->env[i], d->needle, ft_strlen(d->needle)) == 0)
			j++;
		else if (ft_strncmp(d->env[i], arg, ft_strlen(d->env[i])) == 0)
			j++;
		else
		{
			env_copy[i] = d->env[j];
			i++;
			j++;
		}
	}
	return (env_copy);
}

int	unset_set_value(t_argmode *args, t_args	*d, char	*arg)
{
	int		i;
	int		j;
	char	**env_copy;

	i = 0;
	j = 0;
	env_copy = ft_calloc(d->env_len + 2, sizeof(char **));
	env_copy = ft_env_copy(d, i, j, arg);
	d->env = ft_calloc(d->env_len + 2, sizeof(char **));
	i = 0;
	while (env_copy[i])
	{
		d->env[i] = env_copy[i];
		i++;
	}
	return (0);
}

int	check_if_set(t_argmode	*args, t_args	*d, char	*arg)
{
	int	i;

	i = 0;
	d->needle = ft_calloc(ft_strlen(arg), sizeof(char));
	d->needle = ft_strjoin(arg, "=");
	while (d->env[i])
	{
		if (ft_strncmp(d->env[i], d->needle, ft_strlen(d->needle)) == 0)
			unset_set_value(args, d, arg);
		else if (ft_strncmp(d->env[i], arg, ft_strlen(arg)) == 0)
			unset_set_value(args, d, arg);
		i++;
	}
	return (0);
}

void	path_backup(t_args *d)
{
	int	i;

	i = 0;
	while (d->env[i])
	{
		if (strstr(d->env[i], "PWD") != 0)
		{
			d->path_backup = ft_strdup(d->env[i]);
			break ;
		}
		i++;
	}
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
		if (ft_strncmp("PWD", arg[i], 3) == 0)
			path_backup(d);
		check_if_set(args, d, arg[i]);
		i++;
	}
	i = 0;
	return (0);
}
