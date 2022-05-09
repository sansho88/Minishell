/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:46:34 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/09 19:38:31 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	exec_home(t_argmode *argv, int argc, char	*env[])
{
	t_args	data;
	int i;

	i = 0;
	while (i < argc)
	{
		dprintf(1,"Valeur de argc[%d]%s\n", i, argv[i].arg);
		i++;
	}
	data.env = env;
	data.argc = argc;
	data.path = path(env);
	data.acutal_arg = 0;
	if (!data.path)
		exit(EXIT_FAILURE);
	data.pid = malloc(sizeof(int) * argc - 3);
	sorting_hub(&data, argv);
}