/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:46:34 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/10 11:30:03 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	exec_home(t_argmode *argv, int argc, char	*env[])
{
	t_args	data;
	int i;
	int j;

	j = 0;
	i = 0;
	//dprintf(2, "valeur de ARGC : %d || ", argc);
	/*while (argv[i].arg)
	{
		dprintf (2, "valeur de arg : %s\n", argv[i].arg);
		i++;
	}*/
	data.env = env;
	data.argc = argc;
	data.path = path(env);
	data.acutal_arg = 0;
	if (!data.path)
		exit(EXIT_FAILURE);
	data.pid = malloc(sizeof(int) * argc - 3);
	sorting_hub(&data, argv);
}