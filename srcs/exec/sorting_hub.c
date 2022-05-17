/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:57:33 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/17 11:41:54 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	counting_redirections_fwd(t_args *d, t_argmode *argv)
{
	int i;
	
	i = d->acutal_arg;
	while (argv[i].mode == 2)
	{
		i++;
		d->count++;
	}
}

void	counting_redirection_bwd(t_args *d, t_argmode *argv)
{
	int i;
	i = d->acutal_arg;
	while (argv[i].mode == 4)
	{
		i++;
		d->count++;
	}
}
void	sorting_hub(t_args *d, t_argmode *argv)
{
	d->j = 0;
	d->count = 0;
	while (d->acutal_arg < d->argc)
	{
		//dprintf(2, "valeur actuelle de acutal arg : %d\n", d->acutal_arg);
		fork_process(d, argv);
		counting_redirection_bwd(d, argv);
		counting_redirections_fwd(d, argv);
		if (d->count != 0)
		{
			d->acutal_arg = d->acutal_arg + d->count;
			d->count = 0;
		}
		d->acutal_arg++;
		d->j++;
	}
	
}