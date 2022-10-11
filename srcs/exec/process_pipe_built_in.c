/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe_built_in.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:29:36 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/11 11:15:16 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	process_pipe_built_in(t_args *d, t_argmode *argv)
{
	char	**args;
	int		i;
	int		argc;
	int		j;

	j = 0;
	args = ft_split_len(argv[d->acutal_arg].arg, ' ', &argc);
   /* printf("args : %s\n", args[0]);
    while (args[j])
    {
        printf("%s\n", args[j]);
        j++;
    }*/
	j = 0;
	if (d->acutal_arg == 0 && argv[d->acutal_arg].mode == 5)
		exit(127);
	else if (d->acutal_arg == 0)
		pipe_rebuild_first(d, argv);
	else if (d->acutal_arg != 0)
		pipe_rebuild_else(d, argv);
    if (ft_strncmp(&argv->arg[d->acutal_arg], "export", 6) == 0)
		sort_export(argv, d);
    else if (ft_strncmp(&argv->arg[d->acutal_arg], "env", 3) == 0)
		print_env(d);
    else if (ft_strncmp(&argv->arg[d->acutal_arg], "echo", 3) == 0)
        ft_echo(argv[0].arg, d);
	exit(EXIT_SUCCESS);
}
