/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:13:58 by tgriffit          #+#    #+#             */
/*   Updated: 2022/07/25 14:14:03 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

#define HEREDOC_ERROR "Impossible to create a new heredoc"

char	*ft_new_heredocname(int *nb_created)
{
	char		*filename;
	char		*str_nb;
	const char	*ext = ".txt";

	filename = ft_strdup("/tmp/.heredoc");
	str_nb = ft_itoa((*nb_created)++);
	if (!filename || !str_nb)
		perror(HEREDOC_ERROR);
	filename = ft_strjoin_free(filename, str_nb, 2);
	filename = ft_strjoin_free(filename, (char *)ext, 1);
	return (filename);
}

char	*ft_heredoc(char *stop)
{
	char		*filename;
	char		*input;
	int			fd;
	static int	nb_heredocs = 0;

    if (!stop || !*stop)
        return (NULL);
	input = ft_strdup("");
	filename = ft_new_heredocname(&nb_heredocs);
	fd = open(filename, O_CREAT | O_RDWR, 777);
	if (!fd || !filename)
		perror(HEREDOC_ERROR);
	dprintf(2, "STOP is[%s]\n", stop);
	while (ft_strncmp(input, stop, ft_strlen(stop)) != 0)
	{
		//free(input);
		input = readline("> ");
		if (!input || ft_strncmp(input, stop, ft_strlen(stop)) == 0)
			break ;
		ft_putendl_fd(input, fd);
	}
	printf("[END HEREDOC]%s\n", input);
	free(input);
	close(fd);
	return (filename);
}
/*

int main(int argc, char **argv)
{
	char	*stop;

	if (argc != 2)
		stop = "eof";
	else
		stop = argv[1];
	printf("Stop Word is: %s\n", stop);
	ft_heredoc(stop);
}
*/
