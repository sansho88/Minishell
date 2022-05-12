/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:57:33 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/12 17:57:21 by rgeral           ###   ########.fr       */
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
	}
	
}