/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:48:16 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/19 15:43:08 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	set_old_path(t_args *d)
{
	int	j;

	j = 0;
	while (d->env[j])
	{
		if (ft_strncmp("OLDPWD=", d->env[j], 7) == 0)
			break ;
		j++;
	}
	if (j < d->env_len)
	{
		free(d->env[j]);
		d->env[j] = ft_strdup("OLDPWD=");
		d->env[j] = ft_strjoin_free(d->env[j], d->pwd, 1);
	}
	return (0);
}

int	set_pwd(t_args *d)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (d->env[len])
		len++;
	while (d->env[i])
	{
		if (ft_strncmp("PWD=", d->env[i], 4) == 0)
			break ;
		i++;
	}
	if (i < len)
	{
		free(d->env[i]);
		d->env[i] = ft_strdup("PWD=");
		d->env[i] = ft_strjoin_free(d->env[i], d->pwd, 1);
	}
	return (0);
}

int	cd_args_count(char **arg)
{
	int	arg_nbr;

	arg_nbr = 0;
	while (arg[arg_nbr])
		arg_nbr++;
	if (arg_nbr >= 4)
	{
		printf("cd: too many arguments\n");
		return (0);
	}
	else if (arg_nbr == 3)
	{
		printf("cd: string not in pwd: %s\n", arg[1]);
		return (0);
	}
	return (arg_nbr);
}

void	cd_back_sort_pwd(t_args *d, int len, char **pwd_copy)
{
	int	i;

	i = 0;
	if (ft_strncmp(d->pwd, "PWD=/Users", ft_strlen(d->pwd)) == 0)
	{
		d->pwd = ft_calloc(ft_strlen(d->pwd), sizeof(char));
		d->pwd = "PWD=/";
	}
	else
	{
		d->pwd = ft_strdup("/");
		while (i < len)
		{
			d->pwd = ft_strjoin_free(d->pwd, pwd_copy[i], 1);
			if (i < len)
				d->pwd = ft_strjoin_free(d->pwd, "/", 1);
			i++;
		}
	}
}

int	is_valid(char	*arg)
{
	int	i;
	int	j;

	j = 0;
	if (arg[0] == '=')
		return (-1);
	while (arg[j] && arg[j] != '=')
	{
		if ((ft_isalpha(arg[0]) == 0 && arg[0] != '_')
			|| (ft_isalnum(arg[j]) == 0 && arg[j] != '_'))
			return (-1);
		j++;
	}
	i = j;
	if (arg[i] == '=')
		i++;
	while (arg[i])
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_' && arg[i] != '=')
			return (-1);
		i++;
	}
	if (j == 0)
		j = i;
	return (j);
}
