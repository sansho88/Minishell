/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:39:58 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/04 19:11:24 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"


/*void	close_wait(t_args *d, int *tube)
{
	int	i;
	int	status;

	i = 0;
	close(tube[0]);
	close(tube[1]);
	while (i < d->argc - 3)
	{
		waitpid(d->pid[i], &status, 0);
		i++;
	}
}*/
/*
	making Forks then doing processpipe in the son process and check tubes in father process
*/
void	make_fork(int *tube, int *temp_tube, t_args *d, char	*argv[])
{
	int i;

	i = 0;
	if (pipe(temp_tube) == -1)
		perror("pipe is riped\n");
	d->pid[d->j] = fork();
	if (d->pid[d->j] == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (d->pid[d->j] == 0)
	{	
		process_pipe(d, tube, temp_tube, argv);
	}
	if (d->acutal_arg > 1)
	{
		close(tube[0]);
		close(tube[1]);
	}
	
	tube[0] = temp_tube[0];
	tube[1] = temp_tube[1];
}


void	fork_process(t_args *d, char	*argv[])
{
	int	tube[2];
	int	temp_tube[2];
	int	status;
	int	i;

	//pipe(tube);
	//pipe(temp_tube);
	d->acutal_arg = 1;
	d->j = 0;
	while (d->acutal_arg <= d->argc - 1)
	{
		if (ft_strcmp(argv[d->acutal_arg], ">") == 0)
		{
			d->acutal_arg++;
			d->mod = 1;
		}
		else 
			d->mod = 0;
		make_fork(tube, temp_tube, d, argv);
		d->j++;
		d->acutal_arg++;
	}
	i = 0;
	close(tube[0]);
	close(tube[1]);
	while (i < d->argc - 3)
	{
		waitpid(d->pid[i], &status, 0);
		i++;
	}
}