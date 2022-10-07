/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:52:11 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/07 20:29:08 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	execute(t_args *d, char **args, int nb)
{
    char    *tmp;
    int     j;
	int		i;
    int     len;

    len = 0;
	i = 0;
    j = 0;
    /*
        Vérifie tout les path + fonction et check si c'est executable, si oui, execute, "sinon invalid path"
        ex : bin/ls
    */
   if (d->is_path_set == true)
	{
		while (d->path[j])
    	{
        	tmp = ft_strjoin(d->path[j], args[0]);
        	if (access(tmp, F_OK | X_OK) == 0)
        	{
            	break ;
        	}
        	j++;
		}
        while (d->path[len])
            len++;
	}
    if (tmp && d->is_path_set == true && len != j)
    {
        args[0] = tmp;
        execve(args[0], args, d->env);
    }
	else 
		printf("%s: command not found\n", args[0]);
}