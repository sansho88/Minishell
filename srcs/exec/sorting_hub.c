/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:57:33 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/12 19:35:11 by tgriffit         ###   ########.fr       */
.fr       */
=======
/*   Updated: 2022/05/12 19:22:56 by tgriffit         ###   ########.fr       */
>>>>>>> main
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

void	sorting_hub(t_args *d, t_argmode *argv)
{
	d->j = 0;
	d->count = 0;
	while (d->acutal_arg < d->argc)
	{
		dprintf(2, "valeur actuelle de acutal arg : %d\n", d->acutal_arg);
		fork_process(d, argv);
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