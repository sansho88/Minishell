/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:39:58 by rgeral            #+#    #+#             */
/*   Updated: 2022/04/20 15:04:23 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	close_wait(t_args *d, int *tube)
{
	int	i;
	int	status;

	i = 0;
	close(tube[0]);
	close(tube[1]);
	while (i < d->argc - 1)
	{
		waitpid(d->pid[i], &status, 0);
		i++;
	}

}


void	fork_process(t_args *d)
{
	int	i;
	int	tube[2];
	int	temp_tube[2];
	int	status;

	i = 0;
	d->j = 0;
	while (i <= (d->argc))
	{
		make_fork(tube, temp_tube, i, d);
		d->j++;
	}
	close_wait(d, tube);
}