/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:30:27 by rgeral            #+#    #+#             */
/*   Updated: 2022/04/20 14:41:37 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	t_args	data;
	int i;

	i = 0;
	data.argv = argv;
	data.env = env;
	data.argc = argc;
	data.path = path(env);
	data.pid = malloc(sizeof(int) * argc - 3);
	if (!data.path)
		exit(EXIT_FAILURE);
	fork_process(&data);
	free(data.pid);
	return (0);
}