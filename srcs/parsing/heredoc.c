/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:13:58 by tgriffit          #+#    #+#             */
/*   Updated: 2022/06/28 18:52:10 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

#define HEREDOC_ERROR "Impossible to create a new heredoc"

//todo: replacer proprement l'argument ([debug_t_argmode]t_argmode->arg=<< chocapic > b__ t_argmode->mode=5
// [debug_t_argmode]t_argmode->arg=/tmp/.heredoc0.txt__ t_argmode->mode=2
// 	[debug_t_argmode]t_argmode->arg=b__ t_argmode->mode=0
char	*ft_new_heredocname(int *nb_created)
{
	char		*filename;
	char		*str_nb;
	const char	*ext = ".txt";

	filename = ft_strdup("/tmp/.heredoc");
	str_nb = ft_itoa(*nb_created++);
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
	static int	nb_heredocs;

	input = ft_strdup("");
	filename = ft_new_heredocname(&nb_heredocs);
	fd = open(filename, O_CREAT | O_RDWR, 644);
	if (!fd || !filename)
		perror(HEREDOC_ERROR);
	dprintf(2, "STOP is[%s]\n", stop);
	while (ft_strncmp(input, stop, ft_strlen(stop)) != 0)
	{
		//free(input);
		input = readline("> ");
		write(fd, input, ft_strlen(input));
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
