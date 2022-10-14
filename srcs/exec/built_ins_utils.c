/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:19:27 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/14 20:36:28 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	sort_export_tab(t_args *d)
{
	int		i;
	
	i = 0;
	d->sort_env = ft_calloc(d->env_len + 1, sizeof(char **));
	while (d->env[i])
	{
		d->sort_env[i] = ft_calloc(ft_strlen(d->env[i]) + 1, sizeof(char));
		d->sort_env[i] = ft_strdup(d->env[i]);
	//	printf("declare -x %s\n", sort_tab[i]);
		i++;
	}
	sort_tab_exec(d);
	i = 0;
	while (d->sort_env[i])
	{
		printf("declare -x %s\n", d->sort_env[i]);
		//free(d->sort_env[i]);
		i++;
	}
	free_all(d->sort_env);
}

void	sort_export(t_argmode *args, t_args *d)
{
	/*char	**sort_tab;
	int		i;

	sort_tab = d->env;
	sort_tab = sort_tab_exec(d);*/
	sort_export_tab(d);
	/*i = 0;
	while (i < d->env_len)
	{
		printf("declare -x %s\n", d->env[i]);
		i++;
	}*/
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
	//free(d->pwd);
	return (0);
}

int	cd_args_count(t_argmode *args, t_args *d, char **arg)
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
