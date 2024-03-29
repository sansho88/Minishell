/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nigga-tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:08:12 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/24 13:16:44 by tgriffit         ###   ########.fr       */
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

size_t	parse_and_execute(char *commandline, t_args *data)
{
	size_t		nb_args;
	t_argmode	*args;

	args = create_targmode_array(commandline);
	nb_args = 0;
	while (args[nb_args].arg)
		++nb_args;
	if (are_args_ok(args, &nb_args))
	{
		get_signals(true);
		exec_home(args, (int)nb_args, data);
	}
	free_t_argmode(args, &nb_args);
	free(commandline);
	commandline = NULL;
	return (nb_args);
}

int	main(int argc, char *argv[], char	*env[])
{
	char		*commandline;
	size_t		nb_args;
	t_args		data;

	(void)argc;
	(void)argv;
	data.env = init_env(env);
	while (true)
	{
		get_signals(false);
		sign_chars_manager(false);
		commandline = readline(CONCHITO);
		sign_chars_manager(true);
		if (!commandline)
			break ;
		if (*commandline)
			add_history(commandline);
		if (*commandline && is_cmdline_ok(&commandline, data.env))
			nb_args = parse_and_execute(commandline, &data);
		else
			free(commandline);
	}
	printf("CONCHITO has exit the work place\n");
	free_env(nb_args, data);
	clear_history();
}
