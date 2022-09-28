/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nigga-tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:08:12 by tgriffit          #+#    #+#             */
/*   Updated: 2022/09/28 17:56:50 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	merge_cmd_with_args(char **cmd, size_t nb_args)
{
	size_t	i_arg;

	i_arg = 0;
	while (i_arg < nb_args)
	{
		if (ft_strchr(cmd[i_arg], '\"'))
			ft_strjoin(cmd[i_arg - 1], cmd[i_arg]);
		i_arg++;
	}
}

/**
 * Parse the command-line and transforms it with the right args (atoi if needed)
 * @param cmd = The command line
 * @param nb_args = argc-like
 * @return An "argv"-like
 */
char	**parse_command_line(char *cmd, int *nb_args)
{
	char	**cmd_split;

	if (ft_strchr(cmd, '|'))
		cmd_split = ft_split_len(cmd, '|', nb_args);
	else
		cmd_split = ft_split_len(cmd, ' ', nb_args);
	/*if (is_cmdline_ok(cmd))
		return (cmd_split);*/
	while (*nb_args > 0)
		free(cmd_split[*(--nb_args)]);
	return (NULL);
}

int	main(int argc, char *argv[], char	*env[])
{
	char		*commandline;
	t_argmode	*args;
	int			nb_args;
	char		**custom_env;

	commandline = ft_strdup("empty");
	get_signals();
	custom_env = init_env(env);
	while (commandline && ft_strncmp(commandline, "exit", 5))
	{
		free(commandline);
		sign_chars_manager(false);
		commandline = readline(CONCHITO);
		sign_chars_manager(true);
		if (!commandline)
			exit(0);
		add_history(commandline);
		//dprintf(2, "[%s]command line = %s\n", __func__, commandline);
		rl_redisplay();
		if (*commandline && is_cmdline_ok(&commandline, custom_env))
		{
			nb_args = (int)get_nb_seps(commandline) + 1; //forcement au moins 1 arg
			args = create_targmode_array(commandline);
			//debug_t_argmode(args, nb_args);
			if (are_args_ok(args, nb_args))
				exec_home(args, nb_args, custom_env);
		}
	}
	clear_history();
}


