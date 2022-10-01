/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:03:03 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/01 19:05:39 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	add_value(t_argmode *args, t_args *d, char	*arg, char	**env_copy)
{
	int len;
	int i;

	i = 0;
	len = 0;
	while (d->env[len])
		len++;
	env_copy = ft_calloc(len + 2, sizeof(char **));
	while (i < len)
	{
		env_copy[i] = d->env[i];
		i++;
	}
	env_copy[len] = arg;
	d->env = ft_calloc(len + 2, sizeof(char **));
	i = 0;
	while (env_copy[i])
	{
		d->env[i] = env_copy[i];
		i++;
	}
	return (0);
}

int	is_already_set(t_argmode *args, t_args *d, char	*arg)
{
	int i;
	
	i = 0;
	d->needle = ft_calloc(ft_strlen(arg), sizeof(char));
	while (arg[i])
	{
		d->needle[i] = arg[i];
		if (arg[i] == '=')
			if (i == 0)
			{
				printf("export: `%s': not a valid identifier\n", arg);
				return(1);
			}	
			break;
		i++;
	}
	while (d->env[i])
	{
		if (ft_strncmp(d->env[i], d->needle, ft_strlen(d->needle)) == 0)
		{
			d->env[i] = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
			d->env[i] = arg;
			return(1);
		}
		i++;
	}
	return(0);
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
		while (arg[i][j])
		{
			if (is_already_set(args, d, arg[i]) == 0)
					add_value(args, d, arg[i], env_copy);
			j++;
		}
		j = 0;
		i++;
	}
	return(0);
}

int export_hub(t_argmode *args, t_args *d)
{
	char	**arg;
	int i;
	
	i = 0;
	arg = ft_split(args->arg, ' ');
	check_arg(args, d, arg);
	if (!arg[1])
		sort_export(args, d);
    return(0);
}
