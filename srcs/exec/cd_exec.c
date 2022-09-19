/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:58:14 by rgeral            #+#    #+#             */
/*   Updated: 2022/08/30 18:02:57 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"


int cd_args_count(t_argmode *args, t_args *d, char  **arg)
{
    int arg_nbr;
    
    arg_nbr = 0;
    arg = ft_split(args->arg, ' ');
    while (arg[arg_nbr])
    {
        arg_nbr++;
    }
   // printf("nombre d'args : %d\n", arg_nbr);
    if (arg_nbr >= 4)
    {
        printf("cd: too many arguments\n");
        return(0);
    }
    else if (arg_nbr == 3)
    {
        printf("cd: string not in pwd: %s\n", arg[1]);
        return(0);
    }
    return(arg_nbr);
}

int	bwd_to_directory(t_argmode *args, t_args *d,char	**arg)
{
	char	**pwd_copy;
	int len;
	int i;

	i = 0;
	len = 0;
	pwd_copy = ft_calloc(ft_strlen(d->pwd), sizeof(char));
	pwd_copy = ft_split(d->pwd, '/');
	while(pwd_copy[len])
		len++;
	len --;
	if (ft_strncmp(d->pwd, "PWD=/Users", ft_strlen(d->pwd)) == 0)
	{
		d->pwd = ft_calloc(ft_strlen(d->pwd), sizeof(char));
		d->pwd = "PWD=/";
	}
	else
	{
		d->pwd = ft_calloc(ft_strlen(d->pwd), sizeof(char));
		while(i < len)
		{
			d->pwd = ft_strjoin(d->pwd,pwd_copy[i]);
			if (i < len - 1)
				d->pwd = ft_strjoin(d->pwd, "/");
			i++;
		}
	}
	if (chdir(&d->pwd[4]) == -1)
		return(1);
	return(0);
}
int	fwd_to_directory(t_argmode *args, t_args *d,char	**arg)
{
	d->pwd = ft_strjoin(d->pwd, "/");
	d->pwd = ft_strjoin(d->pwd, arg[1]);
	//printf("%s\n", pwd);
	if (chdir(&d->pwd[4]) == -1)
	{
		printf("cd: no such file or directory: %s\n", arg[1]);
		return(1);
	}
	return(0);
}

int only_cd(t_argmode *args, t_args *d,char	**arg)
{
	char	**pwd_copy;
	int i;

	i = 0;
	pwd_copy = ft_calloc(ft_strlen(d->pwd), sizeof(char));
	pwd_copy = ft_split(d->pwd, '/');
	d->pwd = ft_calloc(ft_strlen(d->pwd), sizeof(char));
	while(i < 3)
	{
		d->pwd = ft_strjoin(d->pwd,pwd_copy[i]);
		if (i < 2)
			d->pwd = ft_strjoin(d->pwd, "/");
		i++;
	}
	if (chdir(&d->pwd[4]) == -1)
		return(1);
}

int cd_hub(t_argmode *args, t_args *d)
{
    char    **arg;
    int     args_nbr;
	int i;
	
    i = 0;
	while(d->env[i])
	{
		if(strstr(d->env[i], "PWD") != 0)
			break;	
		i++;
	}
	d->pwd = d->env[i];
    arg = ft_split(args->arg, ' ');
    if  ((args_nbr = cd_args_count(args, d, arg)) == 0)
        return(1);
	if (args_nbr == 2 && ft_strncmp("..", arg[1], 3) != 0)
		fwd_to_directory(args, d, arg);
	else if (args_nbr == 2 && ft_strncmp("..", arg[1], 3) == 0)
		bwd_to_directory(args, d, arg);
	else if (args_nbr == 1 && ft_strncmp("cd", arg[0], 2) == 0)
		only_cd(args, d, arg);
	d->env[i] = d->pwd;
    return(0);
}