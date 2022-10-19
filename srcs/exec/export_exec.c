/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:03:03 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/19 13:08:15 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	add_value(t_args *d, char	*arg, char	**env_copy)
{
	int	i;

	i = 0;
	env_copy = ft_calloc(d->env_len + 2, sizeof(char *));
	while (i < d->env_len)
	{
		env_copy[i] = d->env[i];
		i++;
	}
	env_copy[i] = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	ft_strlcpy(env_copy[i], arg, ft_strlen(arg) + 1);
	free(d->env);
	d->env_len++;
	d->env = env_copy;
	return (0);
}

int	is_valid(char	*arg)
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
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_' && arg[i] != '=')
			return ( -1);
		i++;
	}
	if (j == 0)
		j = i;
	return (j);
}
int	erase_or_not (char	**env, char	*tmp, char	*arg, bool	value)
{
	char	*tmp2;

	tmp2 = ft_strjoin(tmp, "=");
	if (ft_strncmp(*env, tmp, ft_strlen(tmp)) == 0 && ((*env)[ft_strlen(tmp)] == '=' || !(*env)[ft_strlen(tmp)]))
	{
		free(tmp2);
		if (value == true)
		{
			free(*env);
			*env = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
			ft_strlcpy(*env, arg, ft_strlen(arg) + 1);
			return (1);
		}
		else
			return (1);
	}
	else if (ft_strncmp(*env, tmp2, ft_strlen(arg)) == 0 && !(*env)[ft_strlen(arg)])
	{
		free(tmp2);
		if (value == true)
		{
			free(*env);
			*env = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
			ft_strlcpy(*env, arg, ft_strlen(arg) + 1);
			return (1);
		}
		else
			return(1);
	}
	free(tmp2);
	return (0);
}
int	check_if_already_set (t_args *d, char	*arg, int	nb)
{
	int		i;
	char	*tmp;
	bool	value = false;

	i = 0;
	tmp = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	while (i < nb)
	{
		tmp[i] = arg[i];
		i++;
	}
	if (nb < (int)ft_strlen(arg))
		value = true;
	i = 0;
	while (d->env[i])
	{
		if (d->env_len == 0)
			break;
		if (erase_or_not(&d->env[i], tmp, arg, value))
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

int	is_already_set(t_args *d, char	*arg)
{
	int	i;
	int	nb;

	i = 0;
	nb = is_valid(arg);
	if (nb < 0)
	{
		printf("%s : not a valid identifier\n", arg);
		return (1);
	}
	if (check_if_already_set(d, arg, nb))
		return (1);
	return (0);
}

int	check_arg(t_args *d, char **arg)
{
	int		i;
	int		j;
	char	**env_copy;

	i = 1;
	j = 0;
	env_copy = NULL;
	while (arg[i])
	{
		if (is_already_set(d, arg[i]) == 0)
		{
			add_value(d, arg[i], env_copy);
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
		d->is_redirect = true;
		make_fork_built_in(d, args);
		return (0);
	}
	i = 0;
	arg = ft_split(args->arg, ' ');
	check_arg(d, arg);
	if (!arg[1])
		sort_export_tab(d);
	free_all(arg);
	return (0);
}
