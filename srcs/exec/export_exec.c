/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:03:03 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/18 10:36:16 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	add_value(t_argmode *args, t_args *d, char	*arg, char	**env_copy)
{
	int	i;

	i = 0;
	printf("add value // valeur de arg : %s\n", arg);
	env_copy = ft_calloc(d->env_len + 2, sizeof(char *));
	while (i < d->env_len)
	{
		env_copy[i] = d->env[i];
		i++;
	}
	env_copy[i] = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	ft_strlcpy(env_copy[i], arg, ft_strlen(arg) + 1);
	printf("add value // valeur de env_copy : %s\n", env_copy[i]);
	free(d->env);
	d->env_len++;
	d->env = env_copy;
	printf("add value // valeur de env : %s\n", d->env[i]);
	return (0);
}

int	is_valid(t_argmode *args, t_args *d, char	*arg)
{
	int	i;
	int	j;

	j = 0;
	if (arg[0] == '=')
		return ( -1);
	while (arg[j] && arg[j] != '=')
	{
		if (ft_isalpha(arg[0]) == 0 && arg[0] != '_')
			return( -1);
		if (ft_isalnum(arg[j]) == 0 && arg[j] != '_')
			return ( -1);
		j++;
	}
	i = j;
	if (arg[i] == '=')
		i++;
	while (arg[i])
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
			return ( -1);
		i++;
	}
	if (j == 0)
		j = i;
	return (j);
}
int	erase_or_not (char	*env, char	*tmp, char	*arg, bool	value)
{
	char	*tmp2;

	tmp2 = ft_strjoin(tmp, "=");
	if (ft_strncmp(env, tmp, ft_strlen(tmp)) == 0)
	{
		printf("valeur de TMP : %s\n", tmp);
		printf("valeur de TMP2 : %s\n", tmp2);
		printf("valeur de env : %s\n", env);
		printf("valeur de arg : %s\n", arg);
		free(tmp2);
		printf("enter TMP\n");
		if (value == true)
		{
			free(env);
			env = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
			ft_strlcpy(env, arg, ft_strlen(arg) + 1);
			//free(arg);
			return (1);
		}
		else
			return (1);
	}
	else if (ft_strncmp(env, tmp2, ft_strlen(arg)) == 0 && !env[ft_strlen(arg)])
	{
		printf("enter tmp2\n");
		printf("valeur de TMP : %s\n", tmp);
		printf("valeur de TMP2 : %s\n", tmp2);
		printf("valeur de env : %s\n", env);
		printf("valeur de arg : %s\n", arg);
		free(tmp2);
		if (value == true)
		{
			free(env);
			env = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
			ft_strlcpy(env, arg, ft_strlen(arg) + 1);
			//free(arg);
			return (1);
		}
		else
			return(1);
	}
	free(tmp2);
	return (0);
	
}
int	check_if_already_set (t_argmode *args, t_args *d, char	*arg, int	nb)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	bool	value = false;

	i = 0;
	tmp = ft_calloc(ft_strlen(arg)+ 1, sizeof(char));
	while (i < nb)
	{
		tmp[i] = arg[i];
		i++;
	}
	tmp2 = ft_strjoin(tmp, "=");
	if (nb < ft_strlen(arg))
		value = true;
	while (d->env[i])
	{
		/*if (erase_or_not(d->env[i], tmp, arg, value))
		{
			//free(arg);
			free(tmp);
			return (1);
		}*/
		if (ft_strncmp(d->env[i], tmp, ft_strlen(tmp)) == 0)
		{
			free(tmp);
			free(tmp2);
			if (value == true)
			{
				free(d->env[i]);
				d->env[i] = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
				ft_strlcpy(d->env[i], arg, ft_strlen(arg) + 1);
				return (1);
			}
			else
				return (1);
		}
		else if (ft_strncmp(d->env[i], tmp2, ft_strlen(arg)) == 0 && !d->env[i][ft_strlen(arg)])
		{
			free(tmp);
			free(tmp2);
			if (value == true)
			{
				free(d->env[i]);
				d->env[i] = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
				ft_strlcpy(d->env[i], arg, ft_strlen(arg) + 1);
				return (1);
			}
			else
				return(1);
		}
		i++;
	}
	free(tmp);
	free(tmp2);
	return (0);
}

int	is_already_set(t_argmode *args, t_args *d, char	*arg)
{
	int	i;
	int	nb;

	i = 0;
	nb = is_valid(args, d, arg);
	if (nb < 0)
	{
		printf("%s : not a valid identifier\n", arg);
		return (1);
	}
	if (check_if_already_set(args, d, arg, nb))
		return (1);
	return (0);
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
		if (is_already_set(args, d, arg[i]) == 0)
		{
			printf("go in add value\n");
			add_value(args, d, arg[i], env_copy);
		}
		i++;
	}
	return (0);
}

int	export_hub(t_argmode *args, t_args *d)
{
	char	**arg;
	int		i;

	d->is_built_in = true;
	if (d->append_pos != 0 || d->stdout_pos != 0 || args[d->acutal_arg].mode == 1)
	{
		printf("export-fork\n\n");
		d->is_redirect = true;
		make_fork_built_in(d, args);
		return (0);
	}
	i = 0;
	arg = ft_split(args->arg, ' ');
	check_arg(args, d, arg);
	if (!arg[1])
		sort_export(args, d);
	free_all(arg);
	return (0);
}
