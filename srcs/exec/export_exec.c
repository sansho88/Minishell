/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:03:03 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/13 20:59:20 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	add_value(t_argmode *args, t_args *d, char	*arg, char	**env_copy)
{
	int	i;

	i = 0;
	env_copy = ft_calloc(d->env_len + 2, sizeof(char **));
	while (i < d->env_len)
	{
		env_copy[i] = d->env[i];
		i++;
	}
	env_copy[d->env_len] = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	ft_strlcpy(env_copy[d->env_len], arg, ft_strlen(arg) + 1);
	free(d->env);
	d->env = env_copy;
	return (0);
}

int	is_valid(t_argmode *args, t_args *d, char	*arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			if (i == 0)
			{
				printf("export: `%s': not a valid identifier\n", arg);
				return (- 1);
			}	
			break ;
		}
		i++;
	}
	return (i);
}

int	is_already_set(t_argmode *args, t_args *d, char	*arg)
{
	int	i;
	int	nb;

	i = 0;
	nb = is_valid(args, d, arg);
	if (nb < 0)
		return (1);
	while (d->env[i])
	{
		if (ft_strncmp(d->env[i], arg, nb) == 0)
		{
			free(d->env[i]);
			d->env[i] = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
			ft_strlcpy(d->env[i], arg, ft_strlen(arg) + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_arg(t_argmode *args, t_args *d, char **arg)
{
	int		i;
	int		j;
	char	**env_copy;

	i = 1;
	j = 0;
	while (arg[i])
	{
		if (is_already_set(args, d, arg[i]) == 0)
			add_value(args, d, arg[i], env_copy);
		i++;
	}
	return (0);
}

int	export_hub(t_argmode *args, t_args *d)
{
	char	**arg;
	int		i;

	d->is_built_in = true;
	if (d->append_pos != 0 || d->stdout_pos != 0)
	{
		d->is_redirect = true;
		make_fork_built_in(d, args);
		return (0);
	}
	i = 0;
	arg = ft_split(args->arg, ' ');
	check_arg(args, d, arg);
	if (!arg[1])
		sort_export(args, d);
	free_all(arg);
	return (0);
}
