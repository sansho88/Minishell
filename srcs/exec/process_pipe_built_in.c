/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe_built_in.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:29:36 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/25 11:02:55 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	free_process_pipe_built_in(t_args *d)
{
	free_all(d->env);
	free(d->pid);
	free(d->pwd);
	free_all(d->path);
}

void	process_pipe_built_in(t_args *d, t_argmode *argv)
{
	char	**args;

	d->is_built_in = false;
	args = ft_split(argv[d->acutal_arg].arg, ' ');
	if (d->acutal_arg == 0)
		pipe_rebuild_first(d, argv);
	else if (d->acutal_arg != 0)
		pipe_rebuild_else(d, argv);
	if (ft_strncmp(args[0], "export", 6) == 0 && !args[1])
		sort_export_tab(d);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		print_env(d);
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		ft_echo(argv[d->acutal_arg].arg);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		ft_exit(argv[d->acutal_arg].arg, d);
	free_all(args);
	free_process_pipe_built_in(d);
	exit(EXIT_SUCCESS);
}
