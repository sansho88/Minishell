/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:57:33 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/11 13:52:39 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	sorting_hub(t_args *d, t_argmode *argv)
{
	d->j = 0;
	while (d->acutal_arg < d->argc)
	{
		fork_process(d, argv);
		d->j++;
		d->acutal_arg++;
		//dprintf(2 , " valeur de actual arg : %d || valeur de argc : %d valeur de redir fwd : %d \n", d->acutal_arg, d->argc, d->count);
	}
	
}