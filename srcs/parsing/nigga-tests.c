/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nigga-tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:08:12 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/05 10:16:24 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	main(int argc, char *argv[], char	*env[])
{
	char		*commandline;
	t_argmode	*args;
	int			nb_args;
	t_args		data;

	commandline = ft_strdup("empty");
	get_signals();
	data.env = init_env(env);
	while (commandline)
	{
		free(commandline);
		sign_chars_manager(false);
		commandline = readline(CONCHITO);
		sign_chars_manager(true);
		if (!commandline)
			exit(0);
		add_history(commandline);
		rl_redisplay();
		if (*commandline && is_cmdline_ok(&commandline, data.env))
		{
			nb_args = (int)get_nb_seps(commandline) + 1;
			args = create_targmode_array(commandline);
			//debug_t_argmode(args, nb_args);
			if (are_args_ok(args, nb_args))
				exec_home(args, nb_args, &data);
		}
		free_t_argmode(args, nb_args);
	}
	clear_history();
}
