/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:29:36 by rgeral            #+#    #+#             */
/*   Updated: 2022/08/17 14:55:21 by rgeral           ###   ########.fr       */
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
	//dprintf(2, "redirection Bck\n");
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
	//dprintf(2, "redirection fwd\n");
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

	if (d->is_append == 0)
		file = open(argv[d->stdout_pos].arg, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (d->is_append == 1)
		file = open(argv[d->stdout_pos].arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
		//dprintf(2, "test\n");
		ft_forward(d, argv);
	}
	else if (d->is_last == 1)
	{
		//dprintf(2, "ça ecrit\n");
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
		//dprintf(2, "Heyooo\n");
		ft_backward(d, argv);
	}
	else 
	{
		//dprintf(2, "ça read\n");
		ft_dup2(d->temp_tube[0], STDIN_FILENO);
	}
	if (d->stdout_pos != 0)
	{
		ft_forward(d, argv);
	}
	else if (d->is_last == 1)
	{
		//dprintf(2, "ça continue \n\n ");
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
	Dans le cas où il n'y a pas de particularités dans la demande (Pas de pipe, de redirections ..)
	Il faut créer des conditions fonction de ce qu'on me renvoit (redirections)
	*/
	//dprintf(1, "valeur de argv[%d].arg : %s\n \n", d->acutal_arg , argv[d->acutal_arg].arg);
	//dprintf (1, "valeur de d->argc : %d, valeur de actual arg : %d\n", d->argc, d->acutal_arg);
	
	//dprintf(2, "valeur de stdin : %s || %d\n", argv[d->stdin_pos].arg, d->stdin_pos);
	if (d->argc < 2)
		one_arg(d, argv);
	if (d->acutal_arg == 0)
	{
		dprintf(2, "Pipe rebuild first\n");
		pipe_rebuild_first(d, argv);
	}
	else
	{
		//dprintf(2, "rebuild pipex\n");
		pipe_rebuild_else(d, argv);
	}
	//pipe_conditions(d, argv);
	args = ft_split_len(argv[d->acutal_arg].arg, ' ', &argc);
//	dprintf(2, "valeur de acutal arg : %s\n" , args[0]);
	i = 0;
	/*while (args[i])
	{
		dprintf(2, "valeur de args[%d] : %s || argument numéro : %d", i, args[i], d->acutal_arg);
		dprintf(2, " || valeur du mode : %d\n", argv[d->acutal_arg].mode);
		i++;
	}*/
	/*if (d->count != 0)
	{
		d->count++;
		d->acutal_arg = d->acutal_arg + d->count;
		d->count = 0;
	}
	dprintf(2, "valeur de actual arg après opération : %d\n", d->acutal_arg);*/
	if (access(args[0], F_OK | X_OK) == 0)
	{
		execve(args[0], args, d->env);
	}
	execute(d, args, d->acutal_arg);
	exit(EXIT_FAILURE);
}