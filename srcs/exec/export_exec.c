/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:03:03 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/20 09:14:32 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	erase_or_not(char	**env, char	*tmp, char	*arg, bool	value)
{
	char	*tmp2;

	tmp2 = ft_strjoin(tmp, "=");
	if ((ft_strncmp(*env, tmp, ft_strlen(tmp)) == 0 \
		&& ((*env)[ft_strlen(tmp)] == '=' || !(*env)[ft_strlen(tmp)])) || \
		(ft_strncmp(*env, tmp2, ft_strlen(arg)) == 0 && \
	!(*env)[ft_strlen(arg)]))
	{
		free(tmp2);
		if (value == true)
		{
			free(*env);
			*env = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
			if (!*env)
				return (0);
			ft_strlcpy(*env, arg, ft_strlen(arg) + 1);
			return (1);
		}
		else
			return (1);
	}
	free(tmp2);
	return (0);
}

int	check_if_already_set(t_args *d, char *arg, int nb)
{
	int		i;
	char	*tmp;
	bool	value;

	value = false;
	i = -1;
	tmp = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	if (!tmp)
		return (0);
	while (++i < nb)
		tmp[i] = arg[i];
	if (nb < (int)ft_strlen(arg))
		value = true;
	i = 0;
	while (d->env[i])
	{
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
	int	nb;

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
	char	**env_copy;

	i = 1;
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

	d->is_built_in = true;
	if (d->append_pos != 0 || d->stdout_pos != 0 || \
		args[d->acutal_arg].mode == 1 || d->is_piped == true)
	{
		d->is_redirect = true;
		make_fork_built_in(d, args);
		return (0);
	}
	arg = ft_split(args->arg, ' ');
	check_arg(d, arg);
	if (!arg[1])
		sort_export_tab(d);
	free_all(arg);
	return (0);
}
