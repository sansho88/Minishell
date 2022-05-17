/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:57:33 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/17 16:52:07 by rgeral           ###   ########.fr       */
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

void	mode_after_bck_redirection(t_args *d, t_argmode *argv)
{
	int i;

	i = 0;
	while (argv[i].mode == 4 && argv[i + 1].mode && argv[i + 1].mode == 4)
	{
		i++;
	}
	if (argv[i].mode != 0)
	{
		dprintf(2, "Adonis x Roxanne \n");
		d->next_mode = 1;
	}
	
}
void	sorting_hub(t_args *d, t_argmode *argv)
{
	d->j = 0;
	d->count = 0;
	while (d->acutal_arg < d->argc)
	{
		//dprintf(2, "valeur actuelle de acutal arg : %d\n", d->acutal_arg);
		if(argv[d->acutal_arg].mode == 4)
			mode_after_bck_redirection(d, argv);
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