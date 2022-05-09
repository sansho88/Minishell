/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:30:27 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/09 11:39:57 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../incs/pipex.h"
#include "../../incs/minishell.h"

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

int	ft_strcmp(const char	*first, const char	*second)
{
	size_t	i;

	i = 0;
	while (first[i] && (unsigned char)first[i] == \
	(unsigned char)second[i])
		i++;
	return ((unsigned char)first[i] - (unsigned char)second[i]);
}

int	exec_home(t_argmode *argv, int argc, char	*env[])
{
	t_args	data;
	/*int i;

	i = 0;
	//data.argv = argv;
	while (i < argc)
	{
		dprintf(1,"Valeur de argc[%d]%s\n ", i, argv[i].arg);
		i++;
	}*/
	data.env = env; /* I need env variable */
	data.argc = argc;
	data.path = path(env);
	data.pid = malloc(sizeof(int) * argc - 3);
	if (!data.path)
		exit(EXIT_FAILURE);
	fork_process(&data, argv);

	free(data.pid);
	return (0);
}