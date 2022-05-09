/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_mod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:41:35 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/09 20:03:17 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	fork_process(t_args *d, t_argmode *argv)
{
	if (argv[d->acutal_arg].mode == 1)
		make_fork();

}

void	sorting_mod(t_args *d, t_argmode *argv)
{
	if (argv[d->acutal_arg].mode == 1)
		fork_process(d, argv);
	else if (argv[d->acutal_arg].mode == 2)
		redirect_fwd();
}