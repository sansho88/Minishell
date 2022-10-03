/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:57:33 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/01 00:53:37 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_stdin(t_args *d, t_argmode *argv)
{
	int	i;
	int	file;

	i = d->acutal_arg;
	set_back(d, argv, i, file);
	if (argv[i].mode == 0)
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

	i = d->acutal_arg;
	set_fwd(d, argv, i, file2);
	if (argv[i].mode == 0)
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

	i = d->acutal_arg;
	set_append(d, argv, i, file);
	if (argv[i].mode == 0)
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

	i = d->acutal_arg;
	set_heredoc(d, argv, i, file);
	if (argv[i].mode == 0)
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
		d->stdout_pos = 0;
		d->is_append = 0;
		d->append_pos = 0;
		d->acutal_arg++;
		d->j++;
	}
}
