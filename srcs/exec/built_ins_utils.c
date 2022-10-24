/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:19:27 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/24 17:17:37 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	print_export(t_args *d)
{
	int		i;
	int		j;
	bool	set;

	i = 0;
	j = 0;
	while (d->sort_env[i])
	{
		printf("declare -x ");
		set = false;
		j = 0;
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
		printf("%s\n", &"\""[!set]);
		i++;
	}
}

void	sorting_tab(t_args *d, int j)
{
	char	*tmp;

	tmp = d->sort_env[j];
	d->sort_env[j] = d->sort_env[j + 1];
	d->sort_env[j + 1] = tmp;
}

void	sort_export_tab(t_args *d)
{
	int		i;
	int		j;

	i = -1;
	j = 0 ;
	d->sort_env = ft_calloc(d->env_len + 1, sizeof(char *));
	if (!d->sort_env)
		return ;
	while (d->env[++i])
		d->sort_env[i] = d->env[i];
	i = 0;
	while (d->sort_env[i])
	{
		while (j < d->env_len - 1 - i)
		{
			if (strcmp(d->sort_env[j], d->sort_env[j + 1]) > 0)
				sorting_tab(d, j);
			j++;
		}
		j = 0;
		i++;
	}
	print_export(d);
	free(d->sort_env);
}

int	add_value(t_args *d, char	*arg, char	**env_copy)
{
	int	i;

	i = 0;
	env_copy = ft_calloc(d->env_len + 2, sizeof(char *));
	if (!env_copy)
		return (1);
	while (i < d->env_len)
	{
		env_copy[i] = d->env[i];
		i++;
	}
	clean_quotes(arg);
	env_copy[i] = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	if (!env_copy)
		return (1);
	ft_strlcpy(env_copy[i], arg, ft_strlen(arg) + 1);
	free(d->env);
	d->env_len++;
	d->env = env_copy;
	return (0);
}
