/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:07 by rgeral            #+#    #+#             */
/*   Updated: 2022/04/20 18:07:07 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

void	start_process(int *tube, int	*temp_tube, t_args *d)
{

	if (d->argc > 1)
	{
		ft_dup2(temp_tube[1], 1);
		close(temp_tube[1]);
	}
}

void	end_process(int	*tube, t_args	*p)
{
	p = NULL;
	ft_dup2(tube[0], 0);
	close(tube[0]);
}

void	pipe_conditions(int *tube, int	*temp_tube, t_args *d)
{
	if (d->acutal_arg == 1)
	{
			start_process(tube, temp_tube, d);
	}
	/*
	Me donner le nombre d'argument total que je puisse définir le dernier argument
	Pour le end_process
	*/
	if (d->acutal_arg == d->argc - 1)
		end_process (tube, d);
	/*else
		progress_process (tube, temp_tube);*/
}

int	process_pipe(t_args *d, int *tube, int *temp_tube)
{
	char	**args;
	int		i;

	//pipe_conditions(tube, temp_tube, d);
	args = ft_split(d->argv[d->acutal_arg], ' ');
	i = 0;
	while (args[i])
	{
		dprintf(1, "%s\n", args[i]);
		i++;
	}
	if (access(args[0], F_OK | X_OK) == 0)
		execve(args[0], args, d->env);
	execute(d, args, d->acutal_arg);
	exit(EXIT_FAILURE);
}

