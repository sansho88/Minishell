/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:24:24 by rgeral            #+#    #+#             */
/*   Updated: 2022/04/20 13:40:14 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

void	start_process(int *tube, int	*temp_tube, t_args *p)
{
	//int	file;

	//file = open(p->argv[1], 0);
	close(tube[0]);
	ft_dup2(temp_tube[1], 1);
	//ft_dup2(file, 0);
	close(temp_tube[1]);
	//close(file);
}

void	progress_process(int *tube, int	*temp_tube)
{
	ft_dup2(tube[0], 0);
	ft_dup2(temp_tube[1], 1);
	close(tube[0]);
	close(tube[1]);
	close(temp_tube[0]);
	close(temp_tube[1]);
}

void	end_process(int	*tube, t_args	*p)
{
	/*int	file;

	file = open(p->argv[p->argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (file == -1)
	{
		perror("Bad outfile");
		exit(EXIT_FAILURE);
	}*/
	p = NULL;
	close(tube[1]);
	ft_dup2(tube[0], 0);
	//ft_dup2(file, 1);
	close(tube[1]);
	//close(file);
}

void	pipe_conditions(int *tube, int	*temp_tube, t_args *p, int nb)
{
	/*if (nb == 1)
	{
			//start_process(tube, temp_tube, p);
	}*/
	if (nb == p->argc - 2)
		end_process (tube, p);
	else
		progress_process (tube, temp_tube);
}

int	process_pipe(t_args *p, int nb, int *tube, int	*temp_tube)
{
	char	**args;
	int i;

	if (p->argc > 1)
		pipe_conditions(tube, temp_tube, p, nb);
	args = ft_split(p->argv[nb], ' ');
	i = 0;
	while (args[i])
	{
		dprintf(1, "%s\n", args[i]);
		i++;
	}
	if (access(args[0], F_OK | X_OK) == 0)
		execve(args[0], args, p->env);
	execute(p, args, nb);
	exit(EXIT_FAILURE);
}