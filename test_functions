/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:32:03 by rgeral            #+#    #+#             */
/*   Updated: 2022/04/20 09:41:37 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int	ft_strcmp(const char	*first, const char	*second)
{
	size_t	i;

	i = 0;
	while (first[i] && (unsigned char)first[i] == \
	(unsigned char)second[i])
		i++;
	return ((unsigned char)first[i] - (unsigned char)second[i]);
}


int	main(void)
{
	char	*str;
	int		i;
	char	*buffer;
	int		fd;

	i = 0;
	fd = open("test", O_RDWR);
	printf("%d\n", fd);
	buffer = ttyname(fd);
	printf("%s\n", buffer);
	while (ft_strcmp(str, "exit") != 0)
	{
		str = readline("Minishell $> ");
		if(str[0])
			add_history(str);
	}

	printf("%s\n", str);

	return(1);
}