/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:13:58 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/21 17:57:42 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

size_t	ft_tabstrlen(char **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

char	**init_env(char	**env)
{
	char	**new_env;
	size_t	size_env;
	size_t	i;

	if (!env)
		return (NULL);
	size_env = ft_tabstrlen(env);
	new_env = ft_calloc(size_env + 1, sizeof(env));
	if(!new_env)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < size_env)
	{
		new_env[i] = malloc(ft_strlen(env[i]) + 1);
		if(!new_env[i])
			exit(EXIT_FAILURE);
		ft_strlcpy(new_env[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
