/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:57:33 by rgeral            #+#    #+#             */
/*   Updated: 2022/06/22 15:05:05 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	counting_redirections_fwd(t_args *d, t_argmode *argv)
{
	int i;
	
	i = d->acutal_arg;
	while (argv[i].mode == 2)
	{
		i++;
		d->count++;
	}
}

int	counting_redirection_bwd(t_args *d, t_argmode *argv)
{
	int i;
	int file;

	i = d->acutal_arg;
	while (argv[i].mode == 4)
	{
		file = open(argv[i + 1].arg, 1);
		if (file == -1)
		{
			//perror("bad outfile");
			return(1);
		}
		i++;
		d->count++;
		return(0);
	}
}

void	mode_after_bck_redirection(t_args *d, t_argmode *argv)
{
	int i;

	i = 0;
	while (argv[i].mode == 4 && argv[i + 1].mode && argv[i + 1].mode == 4)
	{
		i++;
		d->count++;
	}
	if (argv[i + 1].mode != 0)
	{
		//dprintf(2, "valeur du mode : %d \n", argv[i + 1].mode);
		d->next_mode = 1;
	}
	
}
int target_redirection(t_args *d, t_argmode *argv)
{
	int i;
	int file;
	int file2;
	int file3;

	dprintf(2, "enter target redirection");
	i = d->acutal_arg;
	//dprintf(2, "valeur de i : %d\n", i);
	while(i < d->argc)
	{
		if (argv[i].mode == 1 || argv[i].mode == 0)
			break;
		while(argv[i].mode == 2)
		{
			if (i > 0)
			{
				file = open(argv[i].arg, O_WRONLY | O_TRUNC | O_CREAT, 0666);
				if (file == -1)
				{
					return(1);
				}
			}
			i++;
			d->stdout_pos = i;
			d->is_append = 0;
		}
		if (argv[i].mode == 1 || argv[i].mode == 0)
			break; 
		while (argv[i].mode == 4)
		{
			file2 = open(argv[i + 1].arg, 0666);
				if (file2 == -1)
				{
					dprintf(2, "%s : No such file or directory\n", argv[i + 1].arg);
					return(1);
				}
			i++;
			d->stdin_pos = i;
			close(file2);
		}
		if (argv[i].mode == 1 || argv[i].mode == 0)
			break; 
		while (argv[i].mode == 3)
		{
			file3 = open(argv[i].arg, O_APPEND | O_CREAT);
			if (file == -1)
			{
				return(1);
			}
			i++;
			d->is_append = 1;
			d->stdout_pos = i;
		}
		//dprintf(2, "Valeur pointée : %s\n", argv->arg[i - 1]);
		//i++;
	}
	if (argv[i].mode == 0)
	{
		if (argv[i - 1].mode == 2)
		{
			d->stdout_pos = i;
		}
		else if (argv[i - 1].mode == 4)
		{
			d->stdin_pos = i;
		}
		else if (argv[i - 1].mode == 3)
		{
			d->is_append = 1;
			d->stdout_pos = i;
		}
	}
	//dprintf(2, "valeur de i : %d\n\n", i);
	//d->stdout_pos = 0;
	dprintf(2, "valeur de stdin : %d/%d || valeur de stdout : %d/%d \n", d->stdin_pos, d->argc, d->stdout_pos, d->argc);
	return(0);
}

void	check_if_last(t_args *d, t_argmode *argv)
{
	int i;

	i = d->acutal_arg;
	while (i < d->argc)
	{
		if (argv[i].mode == 1)
		{
			d->is_last = 1;
			break;
		}
		else if (argv[i].mode == 0)
		{
			d->is_last = 0;
			break;
		}
		else 
			i++;
	}
	//dprintf(2, "valeur de is_last : %d\n", d->is_last);
}
int	ft_stdin(t_args *d, t_argmode *argv)
{
	int i;
	int file;

	i = d->acutal_arg;
	while (i < d->argc)
	{
		if (argv[i].mode == 1 || argv[i].mode == 0)
			break; 
		if (argv[i].mode == 4)
		{
			file = open(argv[i + 1].arg, 0666);
				if (file == -1)
				{
					dprintf(2, "%s : No such file or directory\n", argv[i + 1].arg);
					return(1);
				}
			i++;
			d->stdin_pos = i;
			d->redir_count++;
			close(file);
		}
		else 
			i++;
	}
		if (argv[i].mode == 0)
		{
			if (argv[i - 1].mode == 4)
			{
				d->stdin_pos = i;
			}
		}
	//close(file);
	return(0);
}
int	ft_stdout(t_args *d, t_argmode *argv)
{
	int i;
	int file2;
	
	i = d->acutal_arg;
	while (i < d->argc)
	{
		if (argv[i].mode == 1 || argv[i].mode == 0)
			break; 
		if (argv[i].mode == 2)
		{
				file2 = open(argv[i + 1].arg, O_WRONLY | O_TRUNC | O_CREAT, 0666);
				if (file2 == -1)
				{
					return(1);
				}
			i++;
			d->stdout_pos = i;
			d->redir_count++;
			d->is_append = i;
		}
		else 
			i++;
	}
	if (argv[i].mode == 0)
	{
		if (argv[i - 1].mode == 2)
		{
			d->stdout_pos = i;
		}	
	}
	//close(file2);
	return(0);
}

int	ft_append(t_args *d, t_argmode *argv)
{
	int i;
	int file;
	
	i = d->acutal_arg;
	while (i < d->argc)
	{
		if (argv[i].mode == 1 || argv[i].mode == 0)
			break; 
		if (argv[i].mode == 3)
		{
			file = open(argv[i + 1].arg, O_APPEND | O_CREAT, 0644);
			if (file == -1)
			{
				return(1);
			}
			i++;
			d->redir_count++;
			d->append_pos = i;
			close(file);
		}
		else 
			i++;
	}
	if (argv[i].mode == 0)
	{
		if (argv[i - 1].mode == 3)
		{
			d->append_pos = i;
		}
	}
	return(0);
}
void	sorting_hub(t_args *d, t_argmode *argv)
{
	//dprintf(2, "sorting hub enter\n");
	d->j = 0;
	d->count = 0;
	d->is_append = 0;
	d->append_pos = 0;
	while (d->acutal_arg < d->argc)
	{
		d->redir_count = 0;
		/*if ( target_redirection (d, argv) == 1)
		{
			dprintf(2, "bruh\n");
			break;
		}*/
		if (ft_stdin(d, argv) == 1 || ft_stdout(d, argv) == 1 || ft_append(d, argv) == 1)
		{
			//dprintf(2, "bruh\n");
			break;
		}
		//ft_stdin(d, argv);
		//ft_stdout(d, argv);
		//ft_append(d, argv);
		dprintf(2, "valeur de stdin : %d/%d || valeur de stdout : %d/%d || valeur de append : %d/%d\n", d->stdin_pos, d->argc, d->stdout_pos, d->argc, d->append_pos, d->argc);
		check_if_last(d, argv);
		if (d->append_pos > d->stdout_pos)
		{
			d->stdout_pos = d->append_pos;
			d->is_append = 1;
		}
		else
			d->is_append = 0;
		fork_process(d, argv);
		//d->acutal_arg += d->stdin_pos;
		//d->acutal_arg += d->stdout_pos;
		dprintf(2, "valeur de count : %d\n", d->redir_count);
		d->acutal_arg += d->redir_count;
		d->stdin_pos = 0;
		d->stdout_pos = 0;
		d->is_append = 0;
		d->append_pos = 0;
		d->acutal_arg++;
		d->j++;
	}
	
}