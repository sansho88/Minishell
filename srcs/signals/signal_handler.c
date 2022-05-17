/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:20:38 by tgriffit          #+#    #+#             */
/*   Updated: 2022/05/16 18:36:03 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	signal_handler(int signum)
{
	pid_t			mini_pid;

	mini_pid = getpid();
	if (signum == SIGINT)
		ft_putstr_fd("\n"CONCHITO, 1);
	else if (signum == SIGABRT)
	{
		printf("\n[1]\t%d\tabort\t./%s\n", mini_pid, "minishell");
		exit(signum);
	}
}

void	sign_chars_manager(bool turn_on_save)
{
	static struct termios	saved;
	static bool				is_saved = false;
	struct termios			termimi;

	if (!is_saved)
	{
		tcgetattr(STDOUT_FILENO, &saved);
		is_saved = true;
	}
	tcgetattr(STDOUT_FILENO, &termimi);
	termimi.c_lflag &= ~ECHOCTL;
	termimi.c_cc[VQUIT] = 0;
	if (turn_on_save)
		tcsetattr(STDOUT_FILENO, TCSANOW, &saved);
	else
		tcsetattr(STDOUT_FILENO, TCSANOW, &termimi);
}

void	get_signals(void)
{
	signal(SIGABRT, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
