/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nigga-tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:08:12 by tgriffit          #+#    #+#             */
/*   Updated: 2022/04/20 16:33:14 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

/**
 * Parse the command-line and transforms it with the right args (atoi if needed)
 * @param cmd = The command line
 * @param nb_args = argc-like
 * @return An "argv"-like
 */
char	**parse_command_line(char *cmd, int *nb_args)
{
	char	**cmd_split;

	cmd_split = ft_split_len(cmd, ' ', nb_args);
	//free(cmd);
	while (*nb_args > 0)
		free(cmd_split[*(--nb_args)]);
	return (NULL);
}

int	main(int argc, char **argv)
{
	char		*commandline;
	char		**cmd_parsed;
	int			nb_args;
	const char	*prompt = "\033[1;32mConchito \033[93m✗\033[0m ";

	commandline = ft_strdup("empty");
	while (ft_strncmp(commandline, "exit", 5))
	{
		free(commandline);
		commandline = readline(prompt);
		add_history(commandline);
		rl_redisplay();
		cmd_parsed = parse_command_line(commandline, &nb_args);
		free(cmd_parsed);
		printf("nb args entered = %d\n", nb_args);
	}
	free(commandline);
	rl_clear_history();
	exit(0);
}
