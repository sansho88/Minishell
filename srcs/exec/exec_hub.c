/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:46:34 by rgeral            #+#    #+#             */
/*   Updated: 2022/09/30 18:43:26 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"


void	rm_heredoc()
{
	static int	nb_heredoc = 0;
	char 		*tmp;

	tmp = ft_new_heredocname(&nb_heredoc);
	while(access(tmp, R_OK) == 0)
	{
		unlink(tmp);
		free(tmp);
		tmp = ft_new_heredocname(&nb_heredoc);
	}
	free(tmp);
}

int	exec_home(t_argmode *argv, int argc, t_args *d)
{
	//t_args	data;
	int i;
	int j;
	int	status;

	j = 0;
	i = 0;
	//dprintf(2, "valeur de ARGC : %d || ", argc);
	/*while (i < argc)
	{
		dprintf (2, "valeur de arg[%d] : %s || ", i, argv[i].arg);
		dprintf (2, "mode = %d || ", argv[i].mode);
		dprintf (2, "ARGC : %d/%d\n", i, argc );
		i++;
	}*/
	/*while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}*/
	//if (d->env);
	//d->env = env; /*J'ai le droit de faire ça ?? */
	d->count = 0;
	d->argc = argc;
	d->next_mode = 0;
	d->stdin_pos = 0;
	d->stdout_pos = 0;
	//d->redir_fwd = 0;
	d->path = path(d->env);
	d->acutal_arg = 0;
	if (!d->path)
		exit(EXIT_FAILURE);
	// TODO il mank des parenteses
	d->pid = malloc(sizeof(int) * argc - 3);
	sorting_hub(d, argv);
	i = 0;
	while (i < d->argc)
	{
		waitpid(d->pid[i], &status, 0);
		i++;
	}
	rm_heredoc();
}