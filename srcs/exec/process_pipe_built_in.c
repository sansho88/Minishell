/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe_built_in.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:29:36 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/18 10:48:33 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	process_pipe_built_in(t_args *d, t_argmode *argv)
{
	char	**args;
	int		i;
	int		argc;

	d->is_built_in = false;
	args = ft_split_len(argv[d->acutal_arg].arg, ' ', &argc);
	if (d->acutal_arg == 0)
		pipe_rebuild_first(d, argv);
	else if (d->acutal_arg != 0)
		pipe_rebuild_else(d, argv);
	//printf("valeur de is_last : %d\n", d->is_last);
    if (ft_strncmp(&argv->arg[d->acutal_arg], "export", 6) == 0)
		sort_export(argv, d);
    else if (ft_strncmp(&argv->arg[d->acutal_arg], "env", 3) == 0)
		print_env(d);
    else if (ft_strncmp(&argv->arg[d->acutal_arg], "echo", 4) == 0)
        ft_echo(argv[0].arg, d);
	else if (ft_strncmp(&argv->arg[d->acutal_arg], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(&argv->arg[d->acutal_arg], "exit", 4) == 0)
		ft_exit(d, argv);
	exit(EXIT_SUCCESS);
}
