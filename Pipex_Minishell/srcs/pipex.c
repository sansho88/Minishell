/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:35:25 by rgeral            #+#    #+#             */
/*   Updated: 2022/04/20 12:32:26 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include "../incs/pipex.h"
#include <sys/types.h>
#include <sys/wait.h>

char	**path(char	**env)
{
	int		i;
	int		j;
	char	**result;
	char	*temp;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_memcmp(env[i], "PATH=", 5) == 0)
		{
			result = ft_split(&env[i][5], ':');
			while (result[j])
			{
				temp = result[j];
				result[j] = ft_strjoin(result[j], "/");
				free(temp);
				j++;
			}
			return (result);
		}
		i++;
	}
	return (NULL);
}

int	main(int argc, char *argv[], char *env[])
{
	t_args	test;
	int i;


	i = 0;
	/*if (argc <= 4)
	{
		perror("Not enough args");
		exit(EXIT_FAILURE);
	}*/
	test.argv = argv;
	test.env = env;
	test.argc = argc;
	test.path = path(env);
	/*while (test.path[i])
	{
		printf("%s\n", test.path[i]);
		i++;
	}*/
	test.j = 0;
	test.pid = malloc(sizeof(int) * argc - 3);
	if (!test.path)
		exit(EXIT_FAILURE);
	fork_process(&test);
	//do_child_not_war(&test);
	free(test.pid);
	return (0);
}
