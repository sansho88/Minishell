/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe_built_in.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:29:36 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/19 15:51:29 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	process_pipe_built_in(t_args *d, t_argmode *argv)
{
	char	**args;

	d->is_built_in = false;
	args = ft_split(argv[d->acutal_arg].arg, ' ');
	if (d->acutal_arg == 0)
		pipe_rebuild_first(d, argv);
	else if (d->acutal_arg != 0)
		pipe_rebuild_else(d, argv);
	if (ft_strncmp(&argv->arg[d->acutal_arg], "export", 6) == 0)
		sort_export_tab(d);
	else if (ft_strncmp(&argv->arg[d->acutal_arg], "env", 3) == 0)
		print_env(d);
	else if (ft_strncmp(&argv->arg[d->acutal_arg], "echo", 4) == 0)
		ft_echo(argv[0].arg, d);
	else if (ft_strncmp(&argv->arg[d->acutal_arg], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(&argv->arg[d->acutal_arg], "exit", 4) == 0 && \
		d->is_piped == false)
		ft_exit(d, argv);
	free_all(args);
	free_all(d->env);
	free(d->pid);
	free(d->pwd);
	free_all(d->path);
	exit(EXIT_SUCCESS);
}
