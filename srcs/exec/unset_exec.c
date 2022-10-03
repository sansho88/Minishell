/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:53:01 by rgeral            #+#    #+#             */
/*   Updated: 2022/09/30 21:48:00 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	unset_set_value(t_argmode *args, t_args *d, char   *arg)
{
	int		len;
	int		i;
	int		j;
	char	**env_copy;

	i = 0;
	j = 0;
	len = 0;
	while (d->env[len])
		len++;
	env_copy = ft_calloc(len + 1, sizeof(char **));
	while (d->env[j])
	{
		if (ft_strncmp(d->env[i], d->needle, ft_strlen(d->needle)) == 0)
			j++;
		else if (ft_strncmp(d->env[i], arg, ft_strlen(d->env[i])) == 0)
			j++;
		env_copy[i] = d->env[j];
		i++;
		j++;
	}
	d->env = ft_calloc(len + 1, sizeof(char **));
	i = 0;
	while (env_copy[i])
	{
		d->env[i] = env_copy[i];
		i++;
	}
	return (0);
}

int check_if_set(t_argmode *args, t_args *d, char   *arg)
{
    int	i;

	i = 0;
	d->needle = ft_calloc(ft_strlen(arg), sizeof(char));
	d->needle = ft_strjoin(arg, "="); 
	printf("%s\n", arg);
	while (d->env[i])
	{
		if (ft_strncmp(d->env[i], d->needle, ft_strlen(d->needle)) == 0)
			unset_set_value(args, d, arg);
		else if (ft_strncmp(d->env[i], arg, ft_strlen(arg)) == 0)
			unset_set_value(args, d, arg);
		i++;
	}
	return(0);
}

int unset_hub(t_argmode *args, t_args *d)
{
    char	**arg;
	int i;
	
	i = 1;
	arg = ft_split(args->arg, ' ');
    while (arg[i])
    {
        check_if_set(args, d, arg[i]);
        i++;
    }
	i = 0;
/*	while (d->env[i])
	{
		printf("%s\n", d->env[i]);
		i++;	
	}*/
    return(0);
}