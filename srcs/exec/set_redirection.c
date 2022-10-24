/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 23:35:48 by rgeral            #+#    #+#             */
/*   Updated: 2022/10/24 14:11:15 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	set_append(t_args *d, t_argmode *argv, int i, int file)
{
	while (i < d->argc)
	{
		if (argv[i].mode == 1 || argv[i].mode == 0)
			break ;
		if (argv[i].mode == 3)
		{
			clean_quotes(argv[i + 1].arg);
			file = open(argv[i + 1].arg, O_APPEND | O_CREAT, 0644);
			if (file == -1)
				return (1);
			i++;
			d->redir_count++;
			d->append_pos = i;
			close(file);
		}
		else
			i++;
	}
	return (0);
}

int	set_fwd(t_args *d, t_argmode *argv, int i, int file2)
{
	while (i < d->argc)
	{
		if (argv[i].mode == 1 || argv[i].mode == 0)
			break ;
		if (argv[i].mode == 2)
		{
			clean_quotes(argv[i + 1].arg);
			file2 = open(argv[i + 1].arg, O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (file2 == -1)
				return (1);
			i++;
			d->stdout_pos = i;
			d->redir_count++;
			d->is_append = i;
			close(file2);
		}
		else
			i++;
	}
	return (0);
}

int	set_back(t_args *d, t_argmode *argv, int i, int file)
{
	while (i < d->argc)
	{
		if (argv[i].mode == 1 || argv[i].mode == 0)
			break ;
		if (argv[i].mode == 4)
		{
			clean_quotes(argv[i + 1].arg);
			file = open(argv[i + 1].arg, 0666);
			if (file == -1)
			{
				printf("%s : No such file or directory\n", argv[i + 1].arg);
				return (1);
			}
			i++;
			d->stdin_pos = i;
			d->redir_count++;
			close(file);
		}
		else
			i++;
	}
	return (0);
}

int	set_heredoc(t_args *d, t_argmode *argv, int i, int file)
{
	while (i < d->argc)
	{
		if (argv[i].mode == 1 || argv[i].mode == 0)
			break ;
		if (argv[i].mode == 5)
		{
			file = open(argv[i + 1].arg, 0666);
			if (file == -1)
				return (1);
			i++;
			d->redir_count++;
			d->heredoc_pos = i;
			close(file);
		}
		else
			i++;
	}
	return (0);
}

void	is_append_or_heredoc(t_args *d)
{
	if (d->append_pos > d->stdout_pos)
	{
		d->stdout_pos = d->append_pos;
		d->is_append = 1;
	}
	else
		d->is_append = 0;
	if (d->heredoc_pos > d->stdin_pos)
		d->stdin_pos = d->heredoc_pos;
}
