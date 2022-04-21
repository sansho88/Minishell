/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:07 by rgeral            #+#    #+#             */
/*   Updated: 2022/04/21 10:50:05 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

void	start_process(int *tube, int	*temp_tube, t_args *d)
{

	if (d->argc > 2)
	{
		close(tube[0]);
		close(temp_tube[0]);
		ft_dup2(temp_tube[1], STDOUT_FILENO);
		close(temp_tube[1]);
	}
}

void	progress_process(int *tube, int	*temp_tube)
{
	ft_dup2(tube[0], STDIN_FILENO);
	ft_dup2(temp_tube[1], STDOUT_FILENO);
	close(tube[0]);
	close(tube[1]);
	close(temp_tube[0]);
	close(temp_tube[1]);
}

void	end_process(int	*tube, int	*temp_tube)
{
	close(tube[1]);
	ft_dup2(tube[0], STDIN_FILENO);
	close(temp_tube[0]);
	close(tube[0]);
	close (temp_tube[1]);
}

void	pipe_conditions(int *tube, int	*temp_tube, t_args *d)
{
	dprintf(1, "Valeur de actual_arg : %d || Valeur de argc : %d\n", d->acutal_arg, d->argc);
	if (d->acutal_arg == 1)
	{
		start_process(tube, temp_tube, d);
	}
	/*
	Me donner le nombre d'argument total que je puisse définir le dernier argument
	Pour le end_process
	*/

	else if (d->acutal_arg == d->argc - 1)
		end_process (tube, temp_tube);
	else
		progress_process (tube, temp_tube);
	//dprintf(1, "Valeur de actual_arg : %d || Valeur de argc : %d\n", d->acutal_arg, d->argc);
}

int	process_pipe(t_args *d, int *tube, int *temp_tube)
{
	char	**args;
	int		i;

	i = 0;
	pipe_conditions(tube, temp_tube, d);
	args = ft_split(d->argv[d->acutal_arg], ' ');
	if (access(args[0], F_OK | X_OK) == 0)
		execve(args[0], args, d->env);
	execute(d, args, d->acutal_arg);
	exit(EXIT_FAILURE);
}

