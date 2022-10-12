/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:58:14 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/11 17:40:53 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	bwd_to_directory(t_argmode *args, t_args *d, char **arg)
{
	char	**pwd_copy;
	int		len;
	int		i;

	i = 0;
	len = 0;
	pwd_copy = ft_calloc(ft_strlen(d->pwd), sizeof(char));
	pwd_copy = ft_split(d->pwd, '/');
	while (pwd_copy[len])
		len++;
	len --;
	set_old_path(d);
	cd_back_sort_pwd(d, len, pwd_copy);
	if (chdir(d->pwd) == -1)
	{
		printf("bcw not fond\n");
		return (1);
	}
	//free_all(pwd_copy);
	return (0);
}

int	fwd_to_directory(t_argmode *args, t_args *d, char **arg)
{
	char	*tmp;
	int		len;
	int		i;

	tmp = ft_calloc(d->pwd_len + ft_strlen(arg[1]), sizeof(char));
	tmp = getcwd(tmp, 42000);
	tmp = ft_strjoin_free(tmp, "/", 1);
	tmp = ft_strjoin_free(tmp, arg[1], 1);
	if (chdir(tmp) == -1)
	{
		printf("cd: no such file or directory: %s\n", arg[1]);
		return (1);
	}
	else
	{
		set_old_path(d);
		d->pwd = tmp;
	}
	return (0);
}

int	only_cd(t_argmode *args, t_args *d, char **arg)
{
	char	**pwd_copy;
	int		i;

	i = 0;
	set_old_path(d);
	pwd_copy = ft_calloc(ft_strlen(d->pwd), sizeof(char));
	pwd_copy = ft_split(d->pwd, '/');
	d->pwd = ft_calloc(ft_strlen(d->pwd) + 1, sizeof(char));
	d->pwd = ft_strjoin(d->pwd, "/");
	while (i < 2)
	{
		d->pwd = ft_strjoin(d->pwd, pwd_copy[i]);
		if (i < 1)
			d->pwd = ft_strjoin(d->pwd, "/");
		i++;
	}
	if (chdir(d->pwd) == -1)
		return (1);
	return (0);
}

int	direct_path(t_argmode *args, t_args *d, char	**arg)
{
	char	*tmp;

	tmp = arg[1];
	if (chdir(tmp) == -1)
	{
		printf("cd: no such file or directory: %s\n", arg[1]);
		return (1);
	}
	else
		d->pwd = tmp;
	return (0);
}

int	cd_hub(t_argmode *args, t_args *d)
{
	char	**arg;
	int		args_nbr;
	int		i;

	d->is_built_in = true;
	i = 0;
	arg = ft_split(args->arg, ' ');
	args_nbr = cd_args_count(args, d, arg);
	if (args_nbr == 2 && ft_strncmp("/", arg[1], 1) == 0)
		direct_path(args, d, arg);
	else if (args_nbr == 2 && ft_strncmp("..", arg[1], 3) != 0)
		fwd_to_directory(args, d, arg);
	else if (args_nbr == 2 && ft_strncmp("..", arg[1], 3) == 0)
		bwd_to_directory(args, d, arg);
	else if (args_nbr == 1 && ft_strncmp("cd", arg[0], 2) == 0)
		only_cd(args, d, arg);
	set_pwd(d);
	return (0);
}
