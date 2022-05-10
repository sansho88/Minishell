/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:57:33 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/10 13:50:25 by rgeral           ###   ########.fr       */
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
		break;
	}
	
}