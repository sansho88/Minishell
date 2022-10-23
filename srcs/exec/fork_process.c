/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:41:35 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/23 17:29:09 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	is_built_in(t_args *d, t_argmode *argv)
{
	if (ft_strncmp(argv[d->acutal_arg].arg, "cd ", 3) == 0 && d->argc == 1)
		cd_hub(argv, d);
	else if (ft_strncmp(argv[d->acutal_arg].arg, "export ", 7) == 0 || \
	ft_strncmp(argv[d->acutal_arg].arg, "export", 7) == 0)
		export_hub(argv, d);
	else if (ft_strncmp(argv[d->acutal_arg].arg, "env ", 4) == 0)
		env_hub(argv, d);
	else if (ft_strncmp(argv[d->acutal_arg].arg, "unset ", 6) == 0
		&& d->argc == 1)
		unset_hub(argv, d);
	else if (ft_strncmp(argv[d->acutal_arg].arg, "exit ", 5) == 0 || \
		ft_strncmp(argv[d->acutal_arg].arg, "exit", 6) == 0)
		exit_hub(d, argv);
	else if (ft_strncmp(argv[d->acutal_arg].arg, "echo ", 5) == 0)
		echo_hub(argv[0].arg, d, argv);
	else if (ft_strncmp(argv[d->acutal_arg].arg, "pwd ", 4) == 0 || \
		ft_strncmp(argv[d->acutal_arg].arg, "pwd", 4) == 0)
		pwd_hub(argv, d);
	else
		return (0);
	return (1);
}

void	make_fork(t_args *d, t_argmode *argv)
{
	d->pid[d->j] = fork();
	if (d->pid[d->j] == -1)
	{
		perror("fork");
	}
	else if (d->pid[d->j] == 0)
	{
		process_pipe(d, argv);
	}
	if (d->j > 0)
	{
		close(d->temp_tube[0]);
		close(d->temp_tube[1]);
	}
	d->temp_tube[0] = d->tube[0];
	d->temp_tube[1] = d->tube[1];
}

void	make_fork_built_in(t_args *d, t_argmode *argv)
{
	d->pid[d->j] = fork();
	if (d->pid[d->j] == -1)
	{
		perror("fork");
	}
	else if (d->pid[d->j] == 0)
		process_pipe_built_in(d, argv);
	if (d->acutal_arg > 0)
	{
		close(d->temp_tube[0]);
		close(d->temp_tube[1]);
	}
	d->temp_tube[0] = d->tube[0];
	d->temp_tube[1] = d->tube[1];
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
	is_built_in(d, argv);
	if (d->is_built_in == false)
		make_fork(d, argv);
}
