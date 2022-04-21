/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:07 by rgeral            #+#    #+#             */
/*   Updated: 2022/04/20 21:04:13 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

void	start_process(int *tube, int	*temp_tube, t_args *d)
{

	if (d->argc > 2)
	{
		ft_dup2(temp_tube[1], 1);
		close(temp_tube[1]);
		dprintf(1, "test start process\n");
	}
	dprintf(1, "test start process 2\n");
}

void	end_process(int	*tube, int	*temp_tube)
{
	dprintf(1, "test end process\n");
	ft_dup2(tube[0], 0);
	close(tube[0]);
}

void	pipe_conditions(int *tube, int	*temp_tube, t_args *d)
{
	dprintf(1, "Valeur de actual_arg : %d || Valeur de argc : %d\n", d->acutal_arg, d->argc);
	if (d->acutal_arg == 2)
	{
			start_process(tube, temp_tube, d);
	}
	/*
	Me donner le nombre d'argument total que je puisse définir le dernier argument
	Pour le end_process
	*/

	if (d->acutal_arg == d->argc)
		end_process (tube, temp_tube);

	/*else
		progress_process (tube, temp_tube);*/
	//dprintf(1, "Valeur de actual_arg : %d || Valeur de argc : %d\n", d->acutal_arg, d->argc);
}

int	process_pipe(t_args *d, int *tube, int *temp_tube)
{
	char	**args;
	int		i;

	dprintf(1, "nombre de pipe control \n");
	pipe_conditions(tube, temp_tube, d);
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

