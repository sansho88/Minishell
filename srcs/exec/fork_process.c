/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:41:35 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/17 15:18:46 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	is_built_in(t_args *d, t_argmode *argv)
{
	if (ft_strncmp(&argv->arg[d->acutal_arg], "cd ", 3) == 0 && d->argc == 1)
		cd_hub(argv, d);
	else if (ft_strncmp(&argv->arg[d->acutal_arg], "export ", 7) == 0 || ft_strncmp(&argv->arg[d->acutal_arg], "export", 7) == 0)
		export_hub(argv, d);
	else if (ft_strncmp(&argv->arg[d->acutal_arg], "env", 4) == 0)
	{
		printf("env\n\n");
		env_hub(argv, d);
	}
	else if (ft_strncmp(&argv->arg[d->acutal_arg], "unset ", 6) == 0
		&& d->argc == 1)
		unset_hub(argv, d);
	else if (ft_strncmp(&argv->arg[d->acutal_arg], "exit ", 5) == 0)
		ft_exit(d, argv);
	else if (ft_strncmp(&argv->arg[d->acutal_arg], "echo ", 5) == 0)
		echo_hub(argv[0].arg, d, argv);
	else if (ft_strncmp(&argv->arg[d->acutal_arg], "pwd ", 4) == 0)
		pwd_hub(argv, d);
	else
		return (0);
	return (1);
}

void	make_fork(t_args *d, t_argmode *argv)
{
	if (d->is_path_set == true)
	{
		d->pid[d->j] = fork();
		if (d->pid[d->j] == -1)
		{
			perror("fork");
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
	else if (d->is_path_set == false)
		printf("%s :No such file or directory\n", argv[d->acutal_arg].arg);
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
