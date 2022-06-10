/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:46:34 by rgeral            #+#    #+#             */
/*   Updated: 2022/06/10 21:45:59 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	exec_home(t_argmode *argv, int argc, char	*env[])
{
	t_args	data;
	int i;
	int j;

	j = 0;
	i = 0;
	//dprintf(2, "valeur de ARGC : %d || ", argc);
	//dprintf(2, "hello \n\n");
	while (i < argc)
	{
		dprintf (2, "valeur de arg[%d] : %s || ", i, argv[i].arg);
		dprintf (2, "mode = %d || ", argv[i].mode);
		dprintf (2, "ARGC : %d/%d\n", i, argc );
		i++;
	}
	data.env = env;
	data.count = 0;
	data.argc = argc;
	data.next_mode = 0;
	data.stdin_pos = 0;
	data.stdout_pos = 0;
	//data.redir_fwd = 0;
	data.path = path(env);
	data.acutal_arg = 0;
	if (!data.path)
		exit(EXIT_FAILURE);
	data.pid = malloc(sizeof(int) * argc - 3);
	sorting_hub(&data, argv);
}