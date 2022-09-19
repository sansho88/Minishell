/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:03:03 by rgeral            #+#    #+#             */
/*   Updated: 2022/09/08 09:53:27 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char		**add_value(t_argmode *args, t_args *d, char	*arg, char	**env_copy)
{
	int len;
	int i;

	i = 0;
	len = 0;
	while (d->env[len])
		len++;
	env_copy = ft_calloc(len + 2, sizeof(char **));
	while (d->env[i])
	{
		env_copy[i] = d->env[i];
		i++;
	}
	env_copy[len] = arg;
	/*while(i < len + 1)
	{
		printf("%s\n", env_copy[i]);
		i++;
	}*/
	d->env = ft_calloc(len + 2, sizeof(char **));
	i = 0;
	while (env_copy[i])
	{
		d->env[i] = env_copy[i];
		i++;
	}
	return (d->env);
}

char 	**export_hub(t_argmode *args, t_args *d)
{
	char	**arg;
	char	**env_copy;
	int i;
	int	j;
	int len;
	
	i = 0;
	arg = ft_split(args->arg, ' ');
	while (arg[i])
	{
		while (arg[i][j])
		{
			if (arg[i][j] == '=')
				d->env = add_value(args, d, arg[i], env_copy);
			j++;
		}
		j = 0;
		i++;
	}
	i = 0;
	while (d->env[len])
		len++;
	/*while(d->env[i])
	{
		printf("%s\n", d->env[i]);
		i++;
	}*/

    return(d->env);
}