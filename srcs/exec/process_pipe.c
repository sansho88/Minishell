/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:29:36 by rgeral            #+#    #+#             */
/*   Updated: 2022/06/03 18:35:30 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
REDIRECTIONS
*/
void	redirection_bck(t_args *d, t_argmode *argv)
{
	int file;
	int i;
	int j;
	
	j = d->acutal_arg;
	i = d->acutal_arg + 1;
	dprintf(2, "redirection Bck\n");
	//dprintf(2, "nom du fichier : %s\n", argv[i].arg);

	while (argv[j].mode == 4)
	{
		file = open(argv[i].arg, 1);
		if (file == -1)
		{
			perror("bad outfile");
			exit(EXIT_FAILURE);
		}
		ft_dup2(file, STDIN_FILENO);
		close(file);
		j++;
		i++;
	}
}

void	redirection_fwd(t_args *d, t_argmode *argv)
{
	int file;
	int i;
	int j;
	
	j = d->acutal_arg;
	i = d->acutal_arg + 1;
	dprintf(2, "redirection fwd\n");
	//dprintf(2, "nom du fichier : %s\n", argv[2].arg);

	while (argv[j].mode == 2)
	{
		file = open(argv[i].arg, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (file == -1)
		{
			perror("bad outfile");
			exit(EXIT_FAILURE);
		}
		ft_dup2(file, 1);
		close(file);
		j++;
		i++;
	}
}

void	ft_forward(t_args *d, t_argmode *argv)
{
	int file;

	file = open(argv[d->stdout_pos].arg, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file == -1)
	{
		perror("bad outfile");
		exit(EXIT_FAILURE);
	}
	ft_dup2(file, 1);
	close(file);
}
void	ft_backward(t_args *d, t_argmode *argv)
{
	int file2;
	
	file2 = open(argv[d->stdin_pos].arg, 0644);
	if (file2 == -1)
	{
		perror("bad outfile heyo");
		exit(EXIT_FAILURE);
	}
	ft_dup2(file2, STDIN_FILENO);
	close(file2);
}

/*
Processus de pipe normal
*/
/*void	start_process(t_args *d, t_argmode *argv)
{
	
	close(d->temp_tube[0]);
	close(d->tube[0]);
	if (d->stdout_pos != 0)
		ft_forward(d, argv);
//	else 
//		ft_dup2(d->tube[1], STDOUT_FILENO);
	if (d->stdin_pos != 0)
	{
		dprintf(2, "heyo\n");
		ft_backward(d, argv);
	}
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

Les redirections 
*/
/*void	pipe_conditions(t_args *d, t_argmode *argv)
{
	//dprintf(1, "Valeur de actual_arg : %d || Valeur de argc : %d\n", d->acutal_arg, d->argc);
	//dprintf(2, "valeur de argv : %s\n", d->argv[5]);
	if (d->acutal_arg == 0)
	{
		dprintf(2, "start process\n");
		start_process(d, argv);
		/*if (argv[d->acutal_arg].mode == 2)
		{
			redirection_fwd(d, argv);
		}
		if (argv[d->acutal_arg].mode == 4)
		{
			redirection_bck(d, argv);
		}
	}
	
	Me donner le nombre d'argument total que je puisse d??finir le dernier argument
	Pour le end_process
	
	else if (d->acutal_arg == d->argc - 1)
	{
		dprintf(2, "End process\n");
		end_process (d, argv);
	}
	else
	{
		dprintf(2, "progress process\n");
		progress_process (d);
		if (argv[d->acutal_arg].mode == 2)
		{
			redirection_fwd(d, argv);
		}
		if (argv[d->acutal_arg].mode == 4)
		{
			redirection_bck(d, argv);
		}
	}
}*/
void	one_arg(t_args *d, t_argmode *argv)
{
	char	**args;
	int		argc;

	args = ft_split_len(argv[d->acutal_arg].arg, ' ', &argc);
	execute(d, args, d->acutal_arg);
}

void	pipe_rebuild_first(t_args *d, t_argmode *argv)
{
	if (d->stdin_pos != 0)
	{
		ft_backward(d, argv);
	}
	if (d->stdout_pos != 0)
	{
		dprintf(2, "test\n");
		ft_forward(d, argv);
	}
	else if (d->is_last == 1)
	{
		dprintf(2, "??a ecrit\n");
		ft_dup2(d->tube[1], STDOUT_FILENO);
	}
	close(d->tube[1]);
	close(d->tube[0]);
	//close(d->temp_tube[0]);
	//close(d->temp_tube[1]);
	
}

void pipe_rebuild_else(t_args *d, t_argmode *argv)
{
	if (d->stdin_pos != 0)
	{
		dprintf(2, "Heyooo\n");
		ft_backward(d, argv);
	}
	else 
	{
		dprintf(2, "??a read ??? \n");
		ft_dup2(d->temp_tube[0], STDIN_FILENO);
	}
	if (d->stdout_pos != 0)
	{
		ft_forward(d, argv);
	}
	else if (d->is_last == 1)
	{
		dprintf(2, "??a continue \n\n ");
		ft_dup2(d->tube[1], STDOUT_FILENO);
	}
	close(d->tube[1]);
	close(d->tube[0]);
	close(d->temp_tube[0]);
	close(d->temp_tube[1]);
	
}
void    process_pipe(t_args *d, t_argmode *argv)
{
	char	**args;
	int		i;
	int		argc;

	/* 
	Dans le cas o?? il n'y a pas de particularit??s dans la demande (Pas de pipe, de redirections ..)
	Il faut cr??er des conditions fonction de ce qu'on me renvoit (redirections)
	*/
	//dprintf(1, "valeur de argv[%d].arg : %s\n \n", d->acutal_arg , argv[d->acutal_arg].arg);
	//dprintf (1, "valeur de d->argc : %d, valeur de actual arg : %d\n", d->argc, d->acutal_arg);
	
	//dprintf(2, "valeur de stdin : %s || %d\n", argv[d->stdin_pos].arg, d->stdin_pos);
	if (d->argc < 2)
		one_arg(d, argv);
	else if (d->acutal_arg == 0)
	{
		dprintf(2, "Pipe rebuild first\n");
		pipe_rebuild_first(d, argv);
	}
	else
	{
		dprintf(2, "rebuild pipex\n");
		pipe_rebuild_else(d, argv);
	}
	//pipe_conditions(d, argv);
	args = ft_split_len(argv[d->acutal_arg].arg, ' ', &argc);
//	dprintf(2, "valeur de acutal arg : %s\n" , args[0]);
	i = 0;
	/*while (args[i])
	{
		dprintf(2, "valeur de args[%d] : %s || argument num??ro : %d", i, args[i], d->acutal_arg);
		dprintf(2, " || valeur du mode : %d\n", argv[d->acutal_arg].mode);
		i++;
	}*/
	/*if (d->count != 0)
	{
		d->count++;
		d->acutal_arg = d->acutal_arg + d->count;
		d->count = 0;
	}
	dprintf(2, "valeur de actual arg apr??s op??ration : %d\n", d->acutal_arg);*/
	d->stdin_pos = 0;
	d->stdin_pos = 0;
	if (access(args[0], F_OK | X_OK) == 0)
	{
		execve(args[0], args, d->env);
	}
	execute(d, args, d->acutal_arg);
	exit(EXIT_FAILURE);
}