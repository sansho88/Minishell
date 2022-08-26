/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:58:14 by rgeral            #+#    #+#             */
/*   Updated: 2022/08/26 17:38:56 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"


int cd_args_count(t_argmode *args, t_args *d, char  **arg)
{
    int arg_nbr;
    
    arg_nbr = 0;
    arg = ft_split(args->arg, ' ');
    while (arg[arg_nbr])
    {
        arg_nbr++;
    }
    printf("nombre d'args : %d\n", arg_nbr);
    if (arg_nbr >= 4)
    {
        printf("cd: too many arguments\n");
        return(1);
    }
    else if (arg_nbr == 3)
    {
        printf("cd: string not in pwd: %s\n", arg[1]);
        return(1);
    }
    return(0);
}

int cd_hub(t_argmode *args, t_args *d)
{
    char    **arg;
    int     args_nbr;
    
    arg = ft_split(args->arg, ' ');
    if  (cd_args_count(args, d, arg))
        return(1);
    return(0);
}