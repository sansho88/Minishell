/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 00:49:42 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/19 13:40:20 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	check_if_last(t_args *d, t_argmode *argv)
{
	int	i;
	i = 0;
	while (argv[i].mode)
	{
		if (argv[i].mode == 1)
		{
			d->is_piped = true;
			break ;
		}
		i++;
	}
	i = d->acutal_arg;
	while (i < d->argc)
	{
		if (argv[i].mode == 1)
		{
			d->is_last = 1;
			break ;
		}
		else if (argv[i].mode == 0)
		{
			d->is_last = 0;
			break ;
		}
		else
			i++;
	}
}
