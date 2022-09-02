/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:41:35 by rgeral            #+#    #+#             */
/*   Updated: 2022/08/30 18:13:11 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	make_fork(t_args *d, t_argmode *argv)
{
	//dprintf(2, "valeur de actual arg : %d == %s\n", d->acutal_arg, argv[d->acutal_arg].arg);
	if (ft_strncmp(&argv->arg[d->acutal_arg], "cd", 2) == 0 && d->argc == 1)
			cd_hub(argv, d);
	else
	{
		d->pid[d->j] = fork();
		if (d->pid[d->j] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (d->pid[d->j] == 0)
			process_pipe(d, argv);
		if (d->acutal_arg > 0)
		{
			close(d->temp_tube[0]);
			close(d->temp_tube[1]);
		}
		d->temp_tube[0] = d->tube[0];
		d->temp_tube[1] = d->tube[1];
	}
}

void	fork_process(t_args *d, t_argmode *argv)
{
	int	i;

	i = 0;
	if (i != d->argc - 1)
	{
		if (pipe(d->tube) == -1)
			perror("pipe is riped\n");
	}
	make_fork(d, argv);
}
