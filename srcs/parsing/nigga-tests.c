/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nigga-tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:08:12 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/12 17:33:13 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	free_env(size_t	nb_args, t_args data)
{
	nb_args = 0;
	while (data.env[nb_args])
		free(data.env[nb_args++]);
	free(data.env);
}

int	main(int argc, char *argv[], char	*env[])
{
	char		*commandline;
	t_argmode	*args;
	int			nb_args;
	t_args		data;

	get_signals();
	data.env = init_env(env);
	while (true)
	{
		sign_chars_manager(false);
		commandline = readline(CONCHITO);
		sign_chars_manager(true);
		if (!commandline)
			break ;
		add_history(commandline);
		//rl_redisplay();
		if (*commandline && is_cmdline_ok(&commandline, data.env))
		{
			nb_args = (int)get_nb_seps(commandline) + 1;
			args = create_targmode_array(commandline);
			//debug_t_argmode(args, nb_args);
			/*if (are_args_ok(args, nb_args))
				printf("exec\n");*/
			//exec_home(args, nb_args, &data);
			free_t_argmode(args, nb_args);
		}
		free(commandline);
	}
	free_env(nb_args, data);
	clear_history();
}
