/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:57:33 by rgeral            #+#    #+#             */
/*   Updated: 2022/06/06 14:21:30 by rgeral           ###   ########.fr       */
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

void	counting_redirection_bwd(t_args *d, t_argmode *argv)
{
	int i;

	i = d->acutal_arg;
	while (argv[i].mode == 4)
	{
		i++;
		d->count++;
	}
}

void	mode_after_bck_redirection(t_args *d, t_argmode *argv)
{
	int i;

	i = 0;
	while (argv[i].mode == 4 && argv[i + 1].mode && argv[i + 1].mode == 4)
	{
		i++;
	}
	if (argv[i + 1].mode != 0)
	{
		dprintf(2, "valeur du mode : %d \n", argv[i + 1].mode);
		d->next_mode = 1;
	}
	
}
int target_redirection(t_args *d, t_argmode *argv)
{
	int i;
	int file;
	int file2;
	int file3;


	i = d->acutal_arg;
	while(i < d->argc)
	{
		if (argv[i].mode == 1 || argv[i].mode == 0)
			break;
		while(argv[i].mode == 2)
		{
			file = open(argv[i].arg, O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (file == -1)
			{
				return(1);
			}
			i++;
			d->stdout_pos = i;
		}
		if (argv[i].mode == 1 || argv[i].mode == 0)
			break;
		while (argv[i].mode == 4)
		{
			file2 = open(argv[i].arg, 0644);
				if (file == -1)
				{
					dprintf(2, "%s : No such file or directory\n", argv[i].arg);
					return(1);
				}
			i++;
			d->stdin_pos = i;
		}
		/*while (argv[i] == ">>")
		{
			file3 = open(argv[i].arg, O_APPEND | O_CREAT, 0666);
			if (file == -1)
			{
				return(1);
			}
			i++;
			d->stdout_pos = i;
		}*/
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
		/*else if ((argv[i - 1].mode == ">>")
		{
			d->stdout_pos = i;
		}*/
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
	dprintf(2, "valeur de is_last : %d\n", d->is_last);
}

void	sorting_hub(t_args *d, t_argmode *argv)
{
	d->j = 0;
	d->count = 0;
	while (d->acutal_arg < d->argc)
	{
			if ( target_redirection (d, argv) == 1)
		{
			dprintf(2, "bruh");
			break;
		}
		check_if_last(d, argv);
		fork_process(d, argv);
		d->acutal_arg += d->stdin_pos;
		d->acutal_arg += d->stdout_pos;
		d->stdin_pos = 0;
		d->stdout_pos = 0;
		d->acutal_arg++;
		d->j++;
	}
	
}