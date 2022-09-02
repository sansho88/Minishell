/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:13:58 by tgriffit          #+#    #+#             */
/*   Updated: 2022/07/25 14:14:03 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

size_t	ft_tabstrlen(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**init_env(char	**env)
{
	char	**new_env;
	size_t	size_env;
	size_t	i;

	size_env = ft_tabstrlen(env);
	new_env = ft_calloc(size_env,sizeof(env));
	if (!env) {
		return (NULL);
	}
	i = 0;
	while (i < size_env)
	{
		new_env[i] = malloc(ft_strlen(env[i]) + 1);//ft_strjoin(new_env[i], env[i]);
		ft_strlcpy(new_env[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	return (new_env);
}