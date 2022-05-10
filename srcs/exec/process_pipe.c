/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:29:36 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/10 00:48:09 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
REDIRECTIONS
*/
void	redirection(t_args *d, t_argmode *argv)
{
	int file;

	file = open(argv[d->acutal_arg + 1].arg, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file == -1)
	{
		perror("bad outfile");
		exit(EXIT_FAILURE);
	}
	ft_dup2(file, 1);
	close(file);
}

/*
Processus de pipe normal
*/
void	start_process(t_args *d, t_argmode *argv)
{
	close(d->temp_tube[0]);
	close(d->tube[0]);
	ft_dup2(d->tube[1], STDOUT_FILENO);
	close(d->tube[1]);
}

void	progress_process(t_args *d)
{
	
	ft_dup2(d->temp_tube[0], STDIN_FILENO);
	ft_dup2(d->tube[1], STDOUT_FILENO);
	close(d->temp_tube[0]);
	close(d->temp_tube[1]);
	close(d->tube[0]);
	close(d->tube[1]);
}

void	end_process(t_args *d, t_argmode *argv)
{
	close(d->temp_tube[1]);
	ft_dup2(d->temp_tube[0], STDIN_FILENO);
	close(d->tube[0]);
	close(d->temp_tube[0]);
	close (d->tube[1]);
}
/* 
Les redirections 
*/
void	pipe_conditions(t_args *d, t_argmode *argv)
{
	//dprintf(1, "Valeur de actual_arg : %d || Valeur de argc : %d\n", d->acutal_arg, d->argc);
	//dprintf(2, "valeur de argv : %s\n", d->argv[5]);
	if (d->acutal_arg == 0)
	{
		dprintf(2, "Start Process \n");
		start_process(d, argv);
		if (argv[d->acutal_arg].mode == 2)
		{
			redirection(d, argv);
		}
	}
	/*
	Me donner le nombre d'argument total que je puisse définir le dernier argument
	Pour le end_process
	*/
	else if (d->acutal_arg == d->argc - 1)
	{
		dprintf(2, "End process\n");
		end_process (d, argv);
		if (argv[d->acutal_arg].mode == 2)
		{
			redirection(d, argv);
		}
	}
	else
	{
		dprintf(2, "progress process\n");
		progress_process (d);
		if (argv[d->acutal_arg].mode == 2)
		{
			redirection(d, argv);
		}
	}
}

void    process_pipe(t_args *d, t_argmode *argv)
{
	char	**args;
	int		i;
	int		argc;

	/* 
	Dans le cas où il n'y a pas de particularités dans la demande (Pas de pipe, de redirections ..)
	Il faut créer des conditions fonction de ce qu'on me renvoit (redirections)
	*/
	//dprintf(1, "valeur de argv[%d].arg : %s\n \n", d->acutal_arg , argv[d->acutal_arg].arg);
	//dprintf (1, "valeur de d->argc : %d, valeur de actual arg : %d\n", d->argc, d->acutal_arg);
	pipe_conditions(d, argv);
	
	args = ft_split_len(argv[d->acutal_arg].arg, ' ', &argc);
	i = 0;
	while (args[i])
	{
		dprintf(2, "valeur de args[%d] : %s || argument numéro : %d", i, args[i], d->acutal_arg);
		dprintf(2, " || valeur du mode : %d\n", argv[d->acutal_arg].mode);
		i++;
	}
	if (access(args[0], F_OK | X_OK) == 0)
	{
		execve(args[0], args, d->env);
	}
	execute(d, args, d->acutal_arg);
	exit(EXIT_FAILURE);
}