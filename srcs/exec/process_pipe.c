/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:29:36 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/17 18:17:29 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_forward(t_args *d, t_argmode *argv)
{
	int	file;

	if (d->is_append == 0)
		file = open(argv[d->stdout_pos].arg, O_WRONLY
				| O_TRUNC | O_CREAT, 0644);
	else if (d->is_append == 1)
		file = open(argv[d->stdout_pos].arg, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	if (file == -1)
	{
	//	perror("bad outfile");
		exit(EXIT_FAILURE);
	}
	ft_dup2(file, 1);
	close(file);
}

void	ft_backward(t_args *d, t_argmode *argv)
{
	int	file2;

	file2 = open(argv[d->stdin_pos].arg, 0644);
	if (file2 == -1)
	{
		perror("bad outfile");
	}
	ft_dup2(file2, STDIN_FILENO);
	close(file2);
}

void	pipe_rebuild_first(t_args *d, t_argmode *argv)
{
	if (d->stdin_pos != 0)
	{
		ft_backward(d, argv);
	}
	if (d->stdout_pos != 0)
	{
	//	printf("forward\n");
		ft_forward(d, argv);
	}
	else if (d->is_last == 1)
	{
		ft_dup2(d->tube[1], STDOUT_FILENO);
	}
	close(d->tube[1]);
	close(d->tube[0]);
}

void	pipe_rebuild_else(t_args *d, t_argmode *argv)
{
	if (d->stdin_pos != 0)
	{
		ft_backward(d, argv);
	}
	else
	{
		ft_dup2(d->temp_tube[0], STDIN_FILENO);
	}
	if (d->stdout_pos != 0)
	{
		ft_forward(d, argv);
	}
	else if (d->is_last == 1)
	{
		ft_dup2(d->tube[1], STDOUT_FILENO);
	}
	close(d->tube[1]);
	close(d->tube[0]);
	close(d->temp_tube[0]);
	close(d->temp_tube[1]);
}

void	process_pipe(t_args *d, t_argmode *argv)
{
	char	**args;
	int		argc;
	char	*tmp;

	tmp = NULL;
	args = ft_split_len(argv[d->acutal_arg].arg, ' ', &argc);
	if (access(args[0], F_OK | X_OK) == 0)
		execve(args[0], args, d->env);
	tmp = resolve_path(d, args);
	if (d->acutal_arg == 0 && args[0] == NULL)
		exit(127);
	if (d->argc == 1)
		execute(d, args, d->acutal_arg);
	if (!tmp && d->is_built_in == false)
	{
		printf("%s: command not found\n", args[0]);
		exit(127);
	}
	else if (d->acutal_arg == 0)
		pipe_rebuild_first(d, argv);
	else if (d->acutal_arg != 0)
		pipe_rebuild_else(d, argv);
	if (access(args[0], F_OK | X_OK) == 0)
		execve(args[0], args, d->env);
	else if (d->is_built_in == false)
		execute(d, args, d->acutal_arg);
	exit(EXIT_SUCCESS);
}
