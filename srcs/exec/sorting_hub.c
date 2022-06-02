/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:57:33 by rgeral            #+#    #+#             */
/*   Updated: 2022/06/02 18:23:07 by rgeral           ###   ########.fr       */
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

	i = d->acutal_arg + 1;
	while(argv[i].mode != 0 || argv[i].mode == 1)
	{
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
		while (argv[i].mode == 4)
		{
			/*file = open(argv[i].arg, 1);
				if (file == -1)
				{
					dprintf(2, "%s : No such file or directory\n", argv[i].arg);
					return(1);
				}*/
			i++;
			d->stdin_pos = i;
		}
		i++;
	}
	return(0);
	dprintf(2, "valeur de stdin : %d/%d || valeur de stdout : %d/%d \n", d->stdin_pos, d->argc, d->stdout_pos, d->argc);
}

void	check_if_last(t_args *d, t_argmode *argv)
{
	int i;

	i = d->acutal_arg;
	while (argv[i].mode != 1 || argv[i].mode != 0)
	{
		i++;
	}
	if (argv[i].mode == 1)
		d->is_last = 1;
	else if (argv[i].mode == 0)
		d->is_last = 0;
}

void	sorting_hub(t_args *d, t_argmode *argv)
{
	d->j = 0;
	d->count = 0;
	while (d->acutal_arg < d->argc)
	{
	/*	dprintf(2, "valeur actuelle de acutal arg : %d\n", d->acutal_arg);
		if(argv[d->acutal_arg].mode == 4)
			mode_after_bck_redirection(d, argv);
		else
			d->next_mode = 1;		
		*/
		
		
		if ( target_redirection (d, argv) == 1)
		{
			dprintf(2, "bruh");
			break;
		}
		check_if_last(d, argv);
		fork_process(d, argv);
		d->acutal_arg += d->stdin_pos;
		d->acutal_arg += d->stdout_pos;
		/*if (counting_redirection_bwd(d, argv) == 1)
		{
			dprintf(2, "%s : No such file or directory\n", argv[d->acutal_arg + 2].arg);
			break;
		}
		counting_redirections_fwd(d, argv);
		d->next_mode = 0;
		if (d->count != 0)
		{
			d->acutal_arg += d->count;
			d->count = 0;
		}
		else */
		d->stdin_pos = 0;
		d->stdout_pos = 0;
		d->acutal_arg++;
		d->j++;
	}
	
}