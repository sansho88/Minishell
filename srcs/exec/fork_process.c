/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:41:35 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/03 14:51:11 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
int	is_built_in(t_args *d, t_argmode *argv)
{
	if (ft_strncmp(&argv->arg[d->acutal_arg], "cd", 2) == 0 && d->argc == 1)
		return(1);
		//cd_hub(argv, d);
	else if (ft_strncmp(&argv->arg[d->acutal_arg], "export", 6) == 0 && d->argc == 1)
		export_hub(argv, d);
	else if (ft_strncmp(&argv->arg[d->acutal_arg], "env", 3) == 0 && d->argc == 1)
		env_hub(argv, d);
	else if (ft_strncmp(&argv->arg[d->acutal_arg], "unset", 5) == 0 && d->argc == 1)
		unset_hub(argv, d);
	else if (ft_strncmp(&argv->arg[d->acutal_arg], "exit", 4) == 0)
		ft_exit(d, argv);
	else
		return (0);
	return (1);
}
void	make_fork(t_args *d, t_argmode *argv)
{
	if (is_built_in(d, argv) == 0)
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
