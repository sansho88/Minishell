/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:19:27 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/19 13:44:12 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
void	print_export(t_args *d)
{
	int		i;
	int		j;
	bool	set;

	set = false;
	i = 0;
	j = 0;
	while (d->sort_env[i])
	{
		printf("declare -x ");
		while (d->sort_env[i][j])
		{
			printf("%c", d->sort_env[i][j]);
			if (d->sort_env[i][j] == '=' && set == false)
			{
				printf("\"");
				set = true;
			}
			j++;
		}
		if (set == true)
			printf("\"");
		set = false;
		j = 0;
		printf("\n");
		i++;
	}
}
void	sort_export_tab(t_args *d)
{
	int	i;
	int	j;
	char	*tmp;

	i = 0;
	j = 0 ;
	d->sort_env = ft_calloc(d->env_len + 1, sizeof(char *));
	while (d->env[i])
	{
		d->sort_env[i] = d->env[i];
		i++;
	}
	i = 0;
	while (d->sort_env[i])
	{
		
		while (j < d->env_len - 1 - i)
		{
			if (strcmp(d->sort_env[j], d->sort_env[j + 1]) > 0)
			{
				tmp = d->sort_env[j];
				d->sort_env[j] = d->sort_env[j + 1];
				d->sort_env[j + 1] = tmp;
			}
			j++;
		}
		j = 0;
		i++;
	}
	print_export(d);
	free(d->sort_env);
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
