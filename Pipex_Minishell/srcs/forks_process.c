/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:07:17 by rgeral            #+#    #+#             */
/*   Updated: 2022/04/20 12:12:58 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

int	child_generator(int *tube, int	*temp_tube, int i, t_args *p)
{
	if (i != p->argc - 1)
	{
		if (pipe(temp_tube) == -1)
			perror("pipe is riped\n");
	}
	p->pid[p->j] = fork();
	if (p->pid[p->j] == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (p->pid[p->j] == 0)
	{	
		process_pipe(p, i, tube, temp_tube);
	}
	if (i > 2)
	{
		close(tube[0]);
		close(tube[1]);
	}
	tube[0] = temp_tube[0];
	tube[1] = temp_tube[1];
	return (1);
}

void	*do_child_not_war(t_args *p)
{
	int		i;
	int		tube[2];
	int		temp_tube[2];
	int		status;

	i = 1;
	p->j = 0;
	while (++i <= (p->argc - 1))
	{
		child_generator(tube, temp_tube, i, p);
		p->j++;
	}
	close(tube[0]);
	close(tube[1]);
	i = -1;
	while (++i < p->argc - 3)
		waitpid(p->pid[i], &status, 0);
	return (NULL);
}

void	fork_process(t_args *p)
{
	do_child_not_war(p);
}