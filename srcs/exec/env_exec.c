/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:33:32 by rgeral            #+#    #+#             */
/*   Updated: 2022/09/19 15:51:42 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int print_env(t_args *d)
{
    int i;

    i = 0;
    while (d->env[i])
    {
        printf("%s\n", d->env[i]);
        i++;
    }
    return(0);
}

int env_hub(t_argmode *args, t_args *d)
{
    print_env(d);
    return(0);
}