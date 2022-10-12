/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:52:11 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/11 17:17:27 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*resolve_path(t_args *d, char **args)
{
	char	*tmp;
	int j;

	j = 0;
	tmp = NULL;
	if (d->is_path_set == true)
	{
		while (d->path[j])
		{
			tmp = ft_strjoin(d->path[j], args[0]);
			if (access(tmp, F_OK | X_OK) == 0)
				return (tmp);
			free(tmp);
			j++;
		}
	}
	return (NULL);
}

void	execute(t_args *d, char **args, int nb)
{
	char	*tmp;

	tmp = NULL;
	if (d->is_path_set)
		tmp = resolve_path(d, args);
	//free_all(d->path);
	if (tmp && d->is_path_set == true)
	{
		args[0] = tmp;
		execve(args[0], args, d->env);
	}
	else
		printf("%s: command not found\n", args[0]);
	exit(127);
}

// pour chqaue commqnde du pipe
// 	fork -> cherche le path de la cmd (ls -> /bin/ls) -> dup2 et redir -> exec