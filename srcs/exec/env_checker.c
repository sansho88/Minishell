/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:50:11 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/24 18:35:58 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	path_is_set(t_args *d, int pos)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (d->env[pos][i])
	{
		if (d->env[pos][i] == ':')
			len++;
		i++;
	}
	d->path = ft_split(&d->env[pos][5], ':');
	if (!d->path)
		return ;
	i = 0;
	while (i < len)
	{
		d->path[i] = ft_strjoin_free(d->path[i], "/", 1);
		if (!d->path)
			return ;
		i++;
	}
}

void	path_hub(t_args *d)
{
	int	i;

	i = 0;
	d->env_len = 0;
	while (d->env[d->env_len])
		d->env_len++;
	while (d->env[i])
	{
		if (ft_memcmp(d->env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (i < d->env_len)
	{
		path_is_set(d, i);
		d->is_path_set = true;
	}
	else
	{
		d->path = ft_calloc(1, sizeof(char **));
		if (!d->path)
			exit(EXIT_FAILURE);
		d->is_path_set = false;
	}
}
