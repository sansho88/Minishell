/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:57:33 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/24 17:17:37 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_stdin(t_args *d, t_argmode *argv)
{
	int	i;
	int	file;

	file = 0;
	i = d->acutal_arg;
	if (set_back(d, argv, i, file) == 1)
		return (1);
	if (argv[i].mode == 0 && d->argc > 1)
	{
		if (argv[i - 1].mode == 4)
			d->stdin_pos = i;
	}
	return (0);
}

int	ft_stdout(t_args *d, t_argmode *argv)
{
	int	i;
	int	file2;

	file2 = 0;
	i = d->acutal_arg;
	if (set_fwd(d, argv, i, file2) == 1)
		return (1);
	if (argv[i].mode == 0 && d->argc > 1)
	{
		if (argv[i - 1].mode == 2)
		{
			d->stdout_pos = i;
		}	
	}
	return (0);
}

int	ft_append(t_args *d, t_argmode *argv)
{
	int	i;
	int	file;

	file = 0;
	i = d->acutal_arg;
	if (set_append(d, argv, i, file) == 1)
		return (1);
	if (argv[i].mode == 0 && d->argc > 1)
	{
		if (argv[i - 1].mode == 3)
		{
			d->append_pos = i;
		}
	}
	return (0);
}

int	ft_here_doc(t_args *d, t_argmode *argv)
{
	int	i;
	int	file;

	file = 0;
	i = d->acutal_arg;
	if (set_heredoc(d, argv, i, file) == 1)
		return (1);
	if (argv[i].mode == 0 && d->argc > 1)
	{
		if (argv[i - 1].mode == 5)
		{
			d->heredoc_pos = i;
		}
	}
	return (0);
}

void	sorting_hub(t_args *d, t_argmode *argv)
{
	d->stdin_pos = 0;
	d->stdout_pos = 0;
	while (d->acutal_arg < d->argc)
	{
		d->redir_count = 0;
		if (ft_stdin(d, argv) == 1 || ft_stdout(d, argv) == 1
			|| ft_append(d, argv) == 1 || ft_here_doc(d, argv) == 1)
			break ;
		check_if_last(d, argv);
		is_append_or_heredoc(d);
		fork_process(d, argv);
		d->acutal_arg += d->redir_count;
		d->stdin_pos = 0;
		d->is_built_in = false;
		d->is_redirect = false;
		d->stdout_pos = 0;
		d->is_append = 0;
		d->append_pos = 0;
		d->acutal_arg++;
		d->j++;
	}
	close(d->tube[0]);
	close(d->tube[1]);
}
