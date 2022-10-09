/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:19:27 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/08 19:45:55 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	sort_export(t_argmode *args, t_args *d)
{
	char	**sort_tab;
	int		i;
	int		len;

	i = 0;
	while (d->env[len])
		len++;
	sort_tab = d->env;
	sort_tab = sort_tab_exec(sort_tab, len);
	i = 0;
	while (i < len)
	{
		printf("declare -x %s\n", sort_tab[i]);
		i++;
	}
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
		d->pwd = ft_calloc(ft_strlen(d->pwd), sizeof(char));
		d->pwd = ft_strjoin(d->pwd, "/");
		while (i < len)
		{
			d->pwd = ft_strjoin(d->pwd, pwd_copy[i]);
			if (i < len - 1)
				d->pwd = ft_strjoin(d->pwd, "/");
			i++;
		}
	}
}

int	set_old_path(t_args *d)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (d->env[len])
		len++;
	while (d->env[j])
	{
		if (ft_strncmp("OLDPWD=", d->env[j], 7) == 0)
			break ;
		j++;
	}
	if (j < len)
	{
		d->env[j] = ft_calloc(ft_strlen(d->pwd) + 8, sizeof(char));
		d->env[j] = ft_strjoin(d->env[j], "OLDPWD=");
		d->env[j] = ft_strjoin(d->env[j], d->pwd);
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
		d->env[i] = ft_calloc(ft_strlen(d->pwd) + 5, sizeof(char));
		d->env[i] = ft_strjoin(d->env[i], "PWD=");
		d->env[i] = ft_strjoin(d->env[i], d->pwd);
	}
	return (0);
}

int	cd_args_count(t_argmode *args, t_args *d, char **arg)
{
	int	arg_nbr;

	arg_nbr = 0;
	arg = ft_split(args->arg, ' ');
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
