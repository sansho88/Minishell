/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:57:33 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/10 00:16:24 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	one_arg(t_args *d, t_argmode *argv)
{
	char	**args;
	int		argc;

	args = ft_split_len(argv[d->acutal_arg].arg, ' ', &argc);
	execute(d, args, d->acutal_arg);
}

void	sorting_hub(t_args *d, t_argmode *argv)
{
	d->j = 0;
	if (d->argc < 2)
		one_arg(d, argv);
	while (d->acutal_arg < d->argc)
	{
		fork_process(d, argv);
		d->j++;
		d->acutal_arg++;
	}
	
}