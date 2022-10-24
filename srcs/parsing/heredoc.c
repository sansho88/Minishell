/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:13:58 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/24 17:17:37 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

#define HEREDOC_ERROR "Impossible to create a new heredoc"

char	*ft_new_heredocname(int *nb_created)
{
	char		*filename;
	char		*str_nb;

	str_nb = ft_itoa((*nb_created)++);
	filename = ft_strdup("/tmp/.heredoc");
	if (!filename || !str_nb)
		perror(HEREDOC_ERROR);
	filename = ft_strjoin_free(filename, str_nb, 3);
	filename = ft_strjoin_free(filename, ".txt", 1);
	str_nb = NULL;
	return (filename);
}

char	*ft_heredoc(char *stop)
{
	static int	nb_heredocs = 0;
	char		*filename;
	char		*input;
	int			fd;

	if (!stop || !*stop)
		return (NULL);
	filename = ft_new_heredocname(&nb_heredocs);
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd < 0 || !filename)
		perror(HEREDOC_ERROR);
	printf("STOP is [%s]\n", stop);
	input = ft_strdup("");
	while (ft_strncmp(input, stop, ft_strlen(stop) + 1) != 0)
	{
		free(input);
		input = readline("> ");
		if (!input || ft_strncmp(input, stop, ft_strlen(stop) + 1) == 0)
			break ;
		ft_putendl_fd(input, fd);
	}
	free(input);
	close(fd);
	return (filename);
}
