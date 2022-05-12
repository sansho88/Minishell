/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:12:24 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/12 19:35:11 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	execute(t_args *p, char **args, int nb)
{
	char	*tmp;
	int		j;

	j = 0;
	/*
		Vérifie tout les path + fonction et check si c'est executable, si oui, execute, "sinon invalid path"
		ex : bin/ls
	*/

	while (p->path[j])
	{
		tmp = ft_strjoin(p->path[j], args[0]);
		//dprintf(1, "valeur de path[%d] : %s\n", j, p->path[j]);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			break ;
		}
		j++;
	}
	if (access(tmp, F_OK | X_OK) != 0 && nb < p->argc - 1)
	{
		perror("Invalid Path");
	}
	else if (tmp)
	{
		args[0] = tmp;
		execve(args[0], args, p->env);

	}
}