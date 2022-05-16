/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:20:38 by tgriffit          #+#    #+#             */
/*   Updated: 2022/05/16 14:59:44 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	signal_handler(int signum)
{
	pid_t	mini_pid;

	mini_pid = getpid();
	if (signum == SIGINT)
		ft_putstr_fd("\n"CONCHITO, 1);
	else if (signum == SIGABRT)
	{
		ft_putstr_fd("\n[1]\t", 2);
		ft_putnbr_fd(mini_pid, 2);
		ft_putstr_fd("\tabort\t./minishell\n", 2);
		exit(signum);
	}
	else if (signum == SIGQUIT)
		ft_putstr_fd("\n"CONCHITO, 2);
}

void	get_signals(void)
{
	signal(SIGABRT, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
