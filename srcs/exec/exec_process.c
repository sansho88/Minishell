/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:52:11 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/19 09:09:30 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*resolve_path(t_args *d, char **args)
{
	char	*tmp;
	int j;

	j = 0;
	tmp = NULL;
	if (access(args[0], F_OK | X_OK) == 0)
	{
		return (args[0]);
	}
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

void	execute(t_args *d, char **args)
{
	char	*tmp;

	tmp = NULL;
	if (d->is_path_set)
		tmp = resolve_path(d, args);
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