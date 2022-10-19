/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:58:14 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/19 09:29:05 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	bwd_to_directory(t_args *d, char **arg)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	set_old_path(d);
	if (chdir(arg[1]) == -1)
	{
		printf("bcw not fond\n");
		return (1);
	}
	return (0);
}

int	fwd_to_directory(t_args *d, char **arg)
{
	if (chdir(arg[1]) == -1)
	{
		printf("cd: no such file or directory: %s\n", arg[1]);
		return (1);
	}
	else
		set_old_path(d);
	return (0);
}

int	only_cd(t_args *d)
{
	char	**pwd_copy;
	int		i;

	i = 0;
	set_old_path(d);
	pwd_copy = ft_split(d->pwd, '/');
	d->pwd = ft_strdup("/");
	while (i < 2)
	{
		d->pwd = ft_strjoin_free(d->pwd, pwd_copy[i], 1);
		if (i < 1)
			d->pwd = ft_strjoin_free(d->pwd, "/", 1);
		i++;
	}
	if (chdir(d->pwd) == -1)
		return (1);
	free(d->pwd);
	free_all(pwd_copy);
	return (0);
}

int	direct_path(char	**arg)
{

	if (chdir(arg[1]) == -1)
	{
		printf("cd: no such file or directory: %s\n", arg[1]);
		return (1);
	}
	return (0);
}
int	cd_hub(t_argmode *args, t_args *d)
{
	char	**arg;
	int		args_nbr;

	d->is_built_in = true;
	arg = ft_split(args->arg, ' ');
	args_nbr = cd_args_count(arg);
	if (args_nbr == 2 && ft_strncmp("/", arg[1], 1) == 0)
		direct_path(arg);
	else if (args_nbr == 2 && ft_strncmp("..", arg[1], 3) != 0)
		fwd_to_directory(d, arg);
	else if (args_nbr == 2 && ft_strncmp("..", arg[1], 3) == 0)
		bwd_to_directory(d, arg);
	/*else if (ft_strncmp("cd", arg[0], 2) == 0 &&
		ft_strncmp("/Users/robingeral", d->pwd, 18) != 0)
		only_cd(args, d, arg);*/
	//set_pwd(d);
	//char *oldpwd = getcwd(NULL, MAXPATHLEN);
	/*if (chdir(arg[1]) < 0)
	{
		perror("cd");
	}
	else
	{
		printf("Old pwd : %s\n", oldpwd);
	}
	free(oldpwd);*/
	free_all(arg);
	return (0);
}
