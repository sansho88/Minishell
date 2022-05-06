/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:07 by rgeral            #+#    #+#             */
/*   Updated: 2022/05/06 20:08:17 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
/*
Processus de pipe normal
*/
void	start_process(int *tube, int	*temp_tube, t_args *d)
{

	if (d->argc > 1)
	{
		close(tube[0]);
		close(temp_tube[0]);
		ft_dup2(temp_tube[1], STDOUT_FILENO);
		close(temp_tube[1]);
	}
}

void	progress_process(int *tube, int	*temp_tube)
{
	ft_dup2(tube[0], STDIN_FILENO);
	ft_dup2(temp_tube[1], STDOUT_FILENO);
	close(tube[0]);
	close(tube[1]);
	close(temp_tube[0]);
	close(temp_tube[1]);
}

void	end_process(int	*tube, int	*temp_tube)
{
	close(tube[1]);
	ft_dup2(tube[0], STDIN_FILENO);
	close(temp_tube[0]);
	close(tube[0]);
	close (temp_tube[1]);
}
/* 
Les redirections 
*/

/*void redirection_front(int *tube, int *temp_tube, t_args *d, t_argmode *argv)
{
	int	file;

	file = open(argv[d->acutal_arg], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (file == -1)
	{
		perror("bad outfile");
		exit(EXIT_FAILURE);
	}
	ft_dup2(tube[0], STDIN_FILENO);
	temp_tube[1] = file;
	ft_dup2(temp_tube[1], STDOUT_FILENO);
	close(tube[0]);
	close(tube[1]);
	close(temp_tube[0]);
	close(temp_tube[1]);

}

void	redirection_front_last(int *tube, int *temp_tube, t_args *d, t_argmode *argv)
{
	int file;

	file = open(argv[d->acutal_arg], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (file == -1)
	{
		perror("bad outfile");
		exit(EXIT_FAILURE);
	}
	close(tube[1]);
	ft_dup2(tube[0], STDIN_FILENO);
	ft_dup2(file, STDOUT_FILENO);
	close(file);

	close(tube[1]);
	ft_dup2(tube[0], STDIN_FILENO);
	close(temp_tube[0]);
	close(tube[0]);
	close (temp_tube[1]);
	

} */

void	pipe_conditions(int *tube, int	*temp_tube, t_args *d, t_argmode *argv)
{
	//dprintf(1, "Valeur de actual_arg : %d || Valeur de argc : %d\n", d->acutal_arg, d->argc);
	//dprintf(2, "valeur de argv : %s\n", d->argv[5]);
	if (d->acutal_arg == 0)
	{
		dprintf(2, "Start Process \n");
		start_process(tube, temp_tube, d);
	}
	/*
	Me donner le nombre d'argument total que je puisse définir le dernier argument
	Pour le end_process
	*/
	//else if ( d->mod == 1 && d->acutal_arg == d->argc - 1)
	//{
		//dprintf(2,"entrée last_redirection\n");
		//dprintf(2, "valeur de argv : %s\n", argv[d->acutal_arg]);
	//	d->acutal_arg++;
		//redirection_front_last(tube, temp_tube, d, argv);
	//}
	/*else if (d->mod == 1)
	{
		dprintf(2,"entrée redirection\n");
		d->acutal_arg++;
		redirection_front(tube, temp_tube, d, argv);
	}*/

	else if (d->acutal_arg == d->argc - 1)
	{
		dprintf(2, "End process\n");
		end_process (tube, temp_tube);
	}
	else
	{
		dprintf(2, "progress process\n");
		progress_process (tube, temp_tube);
	}
}

int	process_pipe(t_args *d, int *tube, int *temp_tube, t_argmode *argv)
{
	char	**args;
	int		i;
	int		argc;

	/* 
	Dans le cas où il n'y a pas de particularités dans la demande (Pas de pipe, de redirections ..)
	Il faut créer des conditions fonction de ce qu'on me renvoit (redirections)
	*/
	//dprintf(1, "valeur de argv[%d].arg : %s\n \n", d->acutal_arg , argv[d->acutal_arg].arg);
	pipe_conditions(tube, temp_tube, d, argv);
	args = ft_split_len(argv[d->acutal_arg].arg, ' ', &argc);
	i = 0;
	while (i < argc)
	{
		dprintf(2, "valeur de args[%d] : %s || argument numéro : %d\n", i, args[i], d->acutal_arg);
		i++;
	}
	/*if (access(args[0], F_OK | X_OK) == 0)
		execve(args[0], args, d->env);*/
	execute(d, args, d->acutal_arg);
	exit(EXIT_FAILURE);
}

