/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:52:11 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/01 18:59:51 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	execute(t_args *p, char **args, int nb)
{
    char    *tmp;
    int     j;
    j = 0;
    /*
        Vérifie tout les path + fonction et check si c'est executable, si oui, execute, "sinon invalid path"
        ex : bin/ls
    */
    while (p->path[j])
    {
        tmp = ft_strjoin(p->path[j], args[0]);
        if (access(tmp, F_OK | X_OK) == 0)
        {
            break ;
        }
        j++;
    }
    if (tmp)
    {
        args[0] = tmp;
        execve(args[0], args, p->env);
    }
}