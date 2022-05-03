/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:30:27 by rgeral            #+#    #+#             */
/*   Updated: 2022/04/26 11:36:42 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

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